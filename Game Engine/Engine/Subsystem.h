#pragma once

#include "Common.h"

class EventQueue;
class GameObject;
class Component;

class Subsystem
{
public:
	//constructors
	Subsystem(SubsystemType _subsystemType, EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: subsystemType(_subsystemType), eventQueue(_eventQueue), gameObjects(_gameObjects) { gameObjects->reserve(MAX_ENTITIES); }
	Subsystem(const Subsystem& _other) 
		: subsystemType(_other.subsystemType), eventQueue(_other.eventQueue), gameObjects(_other.gameObjects) {};

	//functions
	SubsystemType GetSubsystemType() { return subsystemType; }
	EventQueue* GetEventQueue() { return eventQueue; }
	std::vector<GameObject*>* GetGameObjects() { return gameObjects; }

	virtual void Update() = 0;
	virtual Component* AddComponent(Component* _component) = 0;
	virtual int GetNumOfComponents() = 0;

protected:
	const SubsystemType subsystemType;
	EventQueue* eventQueue;
	std::vector<GameObject*>* gameObjects;
};

