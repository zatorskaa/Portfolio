#pragma once

#include "Common.h"
#include "Subsystem.h"
#include "GameplayComponent.h"

class GameplaySubsystem : public Subsystem
{
public:
	//constructors
	GameplaySubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: Subsystem(SubsystemType::Gameplay, _eventQueue, _gameObjects)
	{
		components = new std::vector<GameplayComponent>;
		components->reserve(MAX_ENTITIES);
	};
	GameplaySubsystem(const GameplaySubsystem& _other)
		: Subsystem(_other)
	{
		components->reserve(MAX_ENTITIES);
	}

	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }

	void Update();
	int GetNumOfComponents() { return components->size(); }

	static bool GetSpawnNetObject() { return spawnNetObject; }
	static void SetSpawnNetObject(bool _spawnNetObject) { spawnNetObject = _spawnNetObject; }

private:
	static bool spawnNetObject; //check if network object is spawned and needs to be updated

	std::vector<GameplayComponent>* components; //list of all gameplay components
};

