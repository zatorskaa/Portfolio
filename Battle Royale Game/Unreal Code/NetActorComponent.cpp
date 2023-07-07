// Fill out your copyright notice in the Description page of Project Settings.


#include "NetActorComponent.h"
#include "NetManager.h" 

int32 UNetActorComponent::lastLocalID = 0;

// Sets default values for this component's properties
UNetActorComponent::UNetActorComponent()
{
	isLocallyOwned = false;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNetActorComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("init"));
	if (isLocallyOwned)
	{
		localID = lastLocalID;
		lastLocalID++;
		UE_LOG(LogTemp, Warning, TEXT("adding"));
		ANetManager::singleton->localNetObjects.Add(this);
	}
	
	ANetManager::singleton->AddNetObject(this); //calls the above method on the singleton network manager
}


// Called every frame
void UNetActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Health %f"), UMyBlueprintFunctionLibrary::GetHealth());
}

//get and set variables
int32 UNetActorComponent::GetGlobalID() {
	return globalID;
}

int32 UNetActorComponent::GetLocalID() {
	return localID;
}

void UNetActorComponent::SetGlobalID(int32 gid) {
	globalID = gid;
}

void UNetActorComponent::SetLocalID(int32 lid) {
	localID = lid;
}

bool UNetActorComponent::GetIsLocallyOwned()
{
	return isLocallyOwned;
}

FString UNetActorComponent::ToPacket() {
	UE_LOG(LogTemp, Warning, TEXT("ToPacket"));
	AActor* parentActor = GetOwner();
	FVector position = parentActor->GetActorLocation();
	FRotator rotation = parentActor->GetActorRotation(); //unreal uses euler angles..
	FQuat quaternionRotation = FQuat(rotation); //so we have to convert to Quaternion for Unity consistence

	//create a string of data to send to other clients
	FString objectData = FString::Printf(TEXT("%f;%i"), UMyBlueprintFunctionLibrary::GetDamage(), ANetManager::packetID); //adds the gun damage and packet id to the packet

	if (UMyBlueprintFunctionLibrary::clientHealth.Num() != 0)
	{
		for (int i = 0; i < UMyBlueprintFunctionLibrary::clientHealth.Num(); i++)
		{
			//checks if a client has been shot
			if (UMyBlueprintFunctionLibrary::isShot[i])
			{
				FString temp = FString::Printf(TEXT("%i"), UMyBlueprintFunctionLibrary::clientID[i]); //if a client has been shot add their id to the packet
				objectData.Append(";");
				objectData.Append(temp);
				objectData.Append(";");
				objectData.Append("1"); //add a shot event (1) to the packet
			}
		}
	}

	//add the client's position and rotation to the packet
	FString returnVal = FString::Printf(TEXT("Object Data;%i;%f;%f;%f;%f;%f;%f;%f;"), globalID,
		position.X,
		position.Y,
		position.Z,
		quaternionRotation.X,
		quaternionRotation.Y,
		quaternionRotation.Z,
		quaternionRotation.W
	);

	//combine all the data into one string
	returnVal.Append(objectData);

	return returnVal;
}

int32 UNetActorComponent::GlobalIDFromPacket(FString packet) {
	TArray<FString> parsed;
	packet.ParseIntoArray(parsed, TEXT(";"), false);
	return FCString::Atoi(*parsed[1]);
}

void UNetActorComponent::FromPacket(FString packet) { //returns global id
	UE_LOG(LogTemp, Warning, TEXT("FromPacket"));
	TArray<FString> parsed;
	packet.ParseIntoArray(parsed, TEXT(";"), false);

	//assign the object's position and rotation values
	AActor* parentActor = GetOwner();
	FVector position = FVector(FCString::Atof(*parsed[2]), FCString::Atof(*parsed[3]), FCString::Atof(*parsed[4]));
	FQuat rotation = FQuat(FCString::Atof(*parsed[5]), FCString::Atof(*parsed[6]), FCString::Atof(*parsed[7]), FCString::Atof(*parsed[8]));
	parentActor->SetActorLocation(position);
	parentActor->SetActorRotation(rotation);
	UE_LOG(LogTemp, Warning, TEXT("ID Recieved: %f"), FCString::Atof(*parsed[9]));

	//check if the same packet has not arrived multiple times by checking if all the values are the same, including the packet id
	if (previousPacket != packet)
	{
		if (parsed.Num() > 10)
		{
			for (int i = 11; i < parsed.Num() - 1; i++)
			{
				//check if the packet has an event with the player's id
				if (FCString::Atof(*parsed[i]) == UMyBlueprintFunctionLibrary::GetPlayerID())
				{
					//check if the event is shot (1)
					if (FCString::Atof(*parsed[i + 1]) == 1)
					{
						UMyBlueprintFunctionLibrary::SetPlayerHealth(UMyBlueprintFunctionLibrary::GetPlayerHealth() - FCString::Atof(*parsed[9]));
					}
				}
			}
		}
		previousPacket = packet; //set the previous packet to the current packet to use to check the next packet
	}
}
