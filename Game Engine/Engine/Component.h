#pragma once

#include "Common.h"

class GameObject;
class Subsystem;

class Component
{
public:
	//constructors
	Component(ComponentType _componentType, GameObject* _gameObject, Subsystem* _subsystem)
		: componentType(_componentType), gameObject(_gameObject), subsystem(_subsystem) {};
	Component(const Component& _other) 
		: componentType(_other.componentType), gameObject(_other.gameObject), subsystem(_other.subsystem) {};

	//functions
	const ComponentType GetComponentType() { return componentType; }
	GameObject* GetGameObject() { return gameObject; }
	Subsystem* GetSubsystem() { return subsystem; }

	virtual void Update() = 0;

protected:
	const ComponentType componentType; //type of component
	GameObject* gameObject; //pointer to the game object that the component belongs to
	Subsystem* subsystem; //pointer to the subsystem that the object belongs to
};

