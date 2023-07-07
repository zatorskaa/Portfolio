// Fill out your copyright notice in the Description page of Project Settings.


#include "NetManager.h"
#include <string>

ANetManager* ANetManager::singleton; //declare the pointer
TArray<UNetActorComponent*> ANetManager::localNetObjects;
int ANetManager::packetID;

// Sets default values
ANetManager::ANetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Socket = nullptr;
}

ANetManager::~ANetManager()
{
 
}

void ANetManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (singleton == nullptr) singleton = this; //if it’s null, it becomes the current instance


	SocketSubsystem = nullptr;
	//more macro code. We’re using Unreal’s low level generic networking (as opposed to it’s higher level game-oriented solution).
	if (SocketSubsystem == nullptr)	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	//packet and buffer sizes
	SendSize = 2 * 1024 * 1024;
	BufferSize = 2 * 1024 * 1024;

	//local endpoint
	LocalEndpoint = FIPv4Endpoint(FIPv4Address::Any, LocalPort);

	FIPv4Address::Parse(IP, RemoteAddress);
	//server endpoint
	RemoteEndpoint = FIPv4Endpoint(RemoteAddress, RemotePort);

	Socket = nullptr;

	if (SocketSubsystem != nullptr)
	{
		if (Socket == nullptr)
		{
			//similar to C#, we use an API to build the socket based on configuration parameters
			Socket = FUdpSocketBuilder(SocketDescription)
				.AsNonBlocking()
				.AsReusable()
				.BoundToEndpoint(LocalEndpoint)
				.WithSendBufferSize(SendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast();
		}
	}
	packetID = 0;


	Listen();
}


// Called when the game starts or when spawned
void ANetManager::BeginPlay()
{
	Super::BeginPlay();
}

void ANetManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ANetManager::localNetObjects.Empty();
	SocketSubsystem->DestroySocket(Socket);
	Socket = nullptr;
	SocketSubsystem = nullptr;
	singleton = nullptr; //it becomes null for next time we play (otherwise it’ll point to the previously destroyed version from the last session

	localNetObjects.Empty(); //this empties the array, so it’s clear next time we start playmode
}

bool ANetManager::sendMessage(FString Message)
{
	if (!Socket) return false;
	int32 BytesSent;

	FTimespan waitTime = FTimespan(10);
	//this is where we create the packet, in this case by serialising the character array
	TCHAR* serializedChar = Message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = Socket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *RemoteEndpoint.ToInternetAddr()); //send message to server
	UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : %s : Address - %s : BytesSent - %d"), *Message, (success ? TEXT("true") : TEXT("false")), *RemoteEndpoint.ToString(), BytesSent);

	if (success && BytesSent > 0) return true;
	else return false;
}

void ANetManager::messageQueue()
{
}

void ANetManager::AddNetObject(UNetActorComponent* component)
{
	//send messages to the server to request UIDs for each local object
	ANetManager::localNetObjects.Add(component);
	if ((component->GetGlobalID() == 0) && (component->GetIsLocallyOwned())) {
		FString t = "I need a UID for local object:" + FString::FromInt(component->GetLocalID());
		sendMessage(t);
	}

}


// Called every frame
void ANetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//send packets to the server with the current data of each object
	for (UNetActorComponent* netObject : ANetManager::localNetObjects) {
		if (netObject->GetIsLocallyOwned() && netObject->GetGlobalID() != 0) {
			UE_LOG(LogTemp, Warning, TEXT("Sending: %s"), *netObject->ToPacket());
			sendMessage(netObject->ToPacket());
		}
	}

	//reset isShot for all clients after a packet with the event has been sent
	if (UMyBlueprintFunctionLibrary::clientHealth.Num() != 0)
	{
		for (int i = 0; i < UMyBlueprintFunctionLibrary::clientHealth.Num(); i++)
		{
			UMyBlueprintFunctionLibrary::isShot[i] = false;
		}
	}

	//increase the packet id (resets back to 0 so it does not go above the max value of an int)
	if (ANetManager::packetID < 300)
	{
		ANetManager::packetID++;
	}
	else
	{
		ANetManager::packetID = 0;
	}

	Listen(); // Listen for messages
}

void ANetManager::Listen()
{
	//recieve packets from the server
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	uint32 Size;
	while (Socket->HasPendingData(Size))
	{
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		Socket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);

		char ansiiData[4096];
		memcpy(ansiiData, ReceivedData.GetData(), BytesRead);
		ansiiData[BytesRead] = 0;

		FString data = ANSI_TO_TCHAR(ansiiData);

		//check if the packet contains a UID to assign to a local object
		if (data.Contains("Assigned UID:")) {

			FString message, info;
			//split off the 'Assigned UID:' bit, by delimiting at the :
			if (data.Split(TEXT(":"), &message, &info)) {
				FString lid, gid;
				//split into local and global ID, by delimiting at the ;
				if (info.Split(TEXT(";"), &lid, &gid)) {

					//the Atoi function is the equivalent of Int32.Parse in C#, converting a string to an int32
					int32 intGlobalID = FCString::Atoi(*gid);
					int32 intLocalID = FCString::Atoi(*lid);

					//iterate netObjects, find the one the local ID corresponds to, and assign the global ID
					for (UNetActorComponent* netObject : ANetManager::localNetObjects) {
						if (netObject->GetLocalID() == intLocalID) {
							netObject->SetGlobalID(intGlobalID);
							UE_LOG(LogTemp, Warning, TEXT("Assigned: %d"), intGlobalID);
						}

					}

				}
			}

		}
		else if (data.Contains("Object Data;")) {
			//check if the recieved string is object data
			UE_LOG(LogTemp, Warning, TEXT("parsing state data"));
			bool foundActor = false;
			for (UNetActorComponent* netObject : ANetManager::localNetObjects) {
				//check if an object with that global id already exists
				if (netObject->GetGlobalID() == netObject->GlobalIDFromPacket(data)) {
					if (!netObject->GetIsLocallyOwned()) {
						netObject->FromPacket(data);
					}
					foundActor = true;
				}
			}

			//if no object exists with that global id then spawn a new object
			if (!foundActor) {
				UE_LOG(LogTemp, Warning, TEXT("spawning"));
				AActor* actor = GetWorld()->SpawnActor<AActor>(OtherPlayerAvatars, FVector::ZeroVector, FRotator::ZeroRotator);
				UNetActorComponent* netActor = actor->FindComponentByClass<UNetActorComponent>();
				netActor->SetGlobalID(netActor->GlobalIDFromPacket(data));
				netActor->FromPacket(data);
			}

		}

	}

}

