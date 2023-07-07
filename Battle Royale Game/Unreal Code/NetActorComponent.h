// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "NetActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TASK_3_API UNetActorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool isLocallyOwned;

	UPROPERTY(VisibleAnywhere)
	int32 globalID;

	UPROPERTY(VisibleAnywhere)
	int32 localID;

	FString previousPacket;

	//UPROPERTY(VisibleAnywhere)
	//UMyBlueprintFunctionLibrary* blueprintClass;

public:
	static int32 lastLocalID;

	UFUNCTION(BlueprintCallable)
	int32 GetGlobalID();

	int32 GetLocalID();
	void SetGlobalID(int32 gID);
	void SetLocalID(int32 lID);
	bool GetIsLocallyOwned();

	void FromPacket(FString packet);
	FString ToPacket();
	int32 GlobalIDFromPacket(FString packet);


public:	
	// Sets default values for this component's properties
	UNetActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
