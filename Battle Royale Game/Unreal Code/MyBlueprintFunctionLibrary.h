// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TASK_3_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()



public:
	//variables to store varaible values from blueprints
	static float playerHealth;
	static int32 playerID;
	static float damage;
	//for the arrays of clients the index of a client's id is the same index for its health is isShot values (if the id is at index 2, that client's health is at index 2)
	static TArray<float> clientHealth;
	static TArray<int32> clientID;
	static TArray<bool> isShot;
	static int32 roundsWon;

	//get and set functions that can be called both in code and in blueprints
	UFUNCTION(BlueprintCallable)
	static void SetPlayerHealth(float _health);

	UFUNCTION(BlueprintCallable)
	static float GetPlayerHealth();

	UFUNCTION(BlueprintCallable)
	static void SetPlayerID(int32 _id);

	UFUNCTION(BlueprintCallable)
	static float GetPlayerID();

	UFUNCTION(BlueprintCallable)
	static void SetDamage(float _damage);

	UFUNCTION(BlueprintCallable)
	static float GetDamage();

	UFUNCTION(BlueprintCallable)
	static void AddClientHealth(float _health, int32 _id);

	UFUNCTION(BlueprintCallable)
	static void SetClientHealth(float _health, int32 _id);

	UFUNCTION(BlueprintCallable)
	static float GetClientHealth(int32 _id);

	UFUNCTION(BlueprintCallable)
	static bool ClientHealthExists(int32 _id);

	UFUNCTION(BlueprintCallable)
	static void SetIsShot(bool _isShot, int32 _id);

	UFUNCTION(BlueprintCallable)
	static float GetIsShot(int32 _id);

	UFUNCTION(BlueprintCallable)
	static void NewArray();

	UFUNCTION(BlueprintCallable)
	static void ResetRoundsWon();

	UFUNCTION(BlueprintCallable)
	static void AddRoundsWon();

	UFUNCTION(BlueprintCallable)
	static int32 GetRoundsWon();
};
