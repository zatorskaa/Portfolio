// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

float UMyBlueprintFunctionLibrary::playerHealth = 0;
int32 UMyBlueprintFunctionLibrary::playerID = 0;
float UMyBlueprintFunctionLibrary::damage = 0;
TArray<float> UMyBlueprintFunctionLibrary::clientHealth = {};
TArray<int32> UMyBlueprintFunctionLibrary::clientID = {};
TArray<bool> UMyBlueprintFunctionLibrary::isShot = {};
int32 UMyBlueprintFunctionLibrary::roundsWon = 0;

void UMyBlueprintFunctionLibrary::SetPlayerHealth(float _health)
{
	playerHealth = _health;
}

float UMyBlueprintFunctionLibrary::GetPlayerHealth()
{
	return playerHealth;
}

void UMyBlueprintFunctionLibrary::SetPlayerID(int32 _id)
{
	playerID = _id;
}

float UMyBlueprintFunctionLibrary::GetPlayerID()
{
	return playerID;
}

void UMyBlueprintFunctionLibrary::SetDamage(float _damage)
{
	damage = _damage;
}

float UMyBlueprintFunctionLibrary::GetDamage()
{
	return damage;
}

void UMyBlueprintFunctionLibrary::AddClientHealth(float _health, int32 _id)
{
	//when a new client joins the game, add them to the arrays
	clientHealth.Add(_health);
	clientID.Add(_id);
	isShot.Add(false);
}

void UMyBlueprintFunctionLibrary::SetClientHealth(float _health, int32 _id)
{
	//find the client's health by using the same array index as the index for its ID
	for (int i = 0; i < clientID.Num(); i++)
	{
		if (_id == clientID[i])
		{
			clientHealth[i] = _health;
		}
	}
}

float UMyBlueprintFunctionLibrary::GetClientHealth(int32 _id)
{
	//find the client's health by using the same array index as the index for its ID
	for (int i = 0; i < clientID.Num(); i++)
	{
		if (_id == clientID[i])
		{
			return clientHealth[i];
		}
	}

	return 0;
}

bool UMyBlueprintFunctionLibrary::ClientHealthExists(int32 _id)
{
	for (int i = 0; i < clientID.Num(); i++)
	{
		if (_id == clientID[i])
		{
			return true;
		}
	}
	return false;
}

void UMyBlueprintFunctionLibrary::SetIsShot(bool _isShot, int32 _id)
{
	//find the client's isShot by using the same array index as the index for its ID
	for (int i = 0; i < clientID.Num(); i++)
	{
		isShot[i] = true;

		if (_id == clientID[i])
		{
			isShot[i] = true;
			UE_LOG(LogTemp, Warning, TEXT("Shot"));
		}
	}
}

float UMyBlueprintFunctionLibrary::GetIsShot(int32 _id)
{
	//find the client's isShot by using the same array index as the index for its ID
	for (int i = 0; i < clientID.Num(); i++)
	{
		if (_id == clientID[i])
		{
			return isShot[i];
		}
	}

	return 0;
}

void UMyBlueprintFunctionLibrary::NewArray()
{
	clientHealth = {};
	clientID = {};
	isShot = {};
}

void UMyBlueprintFunctionLibrary::ResetRoundsWon()
{
	roundsWon = 0;
}

void UMyBlueprintFunctionLibrary::AddRoundsWon()
{
	roundsWon++;
}

int32 UMyBlueprintFunctionLibrary::GetRoundsWon()
{
	return roundsWon;
}
