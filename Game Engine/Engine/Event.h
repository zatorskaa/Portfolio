#pragma once

#include "Common.h"

class GameObject;

class Event
{
public:
	//constructors
	Event(EventType _eventType, std::vector<GameObject*> _gameObjects, std::vector<SubsystemType> _subsystemTypes)
		: eventType(_eventType), gameObjects(_gameObjects), subsystemTypes(_subsystemTypes) {};
	Event() { eventType = EventType::Unassigned; }
	Event(const Event& _other) 
		: eventType(_other.eventType), gameObjects(_other.gameObjects), subsystemTypes(_other.subsystemTypes) {};

	Event& operator=(const Event& _other) 
	{ 
		if (this == &_other) 
			return *this; 

		Event a(_other.eventType, _other.gameObjects, _other.subsystemTypes);
		return a; 
	};

	//functions
	void AssignEventType(EventType _eventType) { eventType = _eventType; }
	void AssignObjects(std::vector<GameObject*> _gameObjects) { gameObjects = _gameObjects; }
	void AssignSubsystemType(std::vector<SubsystemType> _subsystemTypes) { subsystemTypes = _subsystemTypes; }

	EventType eventType; //the type of event
	std::vector<GameObject*> gameObjects; //pointer to the game objects that are in the event
	std::vector<SubsystemType> subsystemTypes; //list of subsystem types that are in the event#
};