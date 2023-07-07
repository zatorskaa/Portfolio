// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //default UE library
#include "GameFramework/Actor.h" //class we're extending
#include "Networking.h" //networking module
#include "NetActorComponent.h"
#include "NetManager.generated.h" //last include statement

UCLASS() //insert boilerplate UE code
class TASK_3_API ANetManager : public AActor
{
	GENERATED_BODY() //insert boilerplate UE code
	
public:	
	// Sets default values for this actor's properties
	ANetManager();
	~ANetManager();

	static ANetManager* singleton; //declare the class to contain a pointer to an instance of itself
	static TArray<UNetActorComponent*> localNetObjects; //stores all the connected net objects

	//network variables
	FSocket* Socket;

	//Local Endpoint
	FString SocketDescription = "UDP Listen Socket";
	FIPv4Endpoint LocalEndpoint;
	uint16 LocalPort = 0;
	int32 SendSize;
	TArray<uint8> ReceivedData;

	//Remote Endpoint
	FIPv4Endpoint RemoteEndpoint;
	FIPv4Address RemoteAddress;
	uint16 RemotePort = 9050;
	int32 BufferSize;
	//FString IP = "10.0.74.149";
	FString IP = "192.168.1.174";

	ISocketSubsystem* SocketSubsystem;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> OtherPlayerAvatars;

	static int packetID; //a unique packet id for each packet to check if a client has recieved the same packet more than once

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Listen();

	UFUNCTION(BlueprintCallable, Category = "UDPNetworking")
		bool sendMessage(FString Message);

	void messageQueue();

	void AddNetObject(UNetActorComponent* component);
};
