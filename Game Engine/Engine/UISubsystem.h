#pragma once

#include <SFML\Graphics.hpp>

#include "Common.h"
#include "Subsystem.h"
#include "UIComponent.h"

class UISubsystem : public Subsystem
{
public:
	//constructors
	UISubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: Subsystem(SubsystemType::UI, _eventQueue, _gameObjects)
	{
		components = new std::vector<UIComponent>;
		components->reserve(MAX_ENTITIES);
	};


	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }

	void Update();
	int GetNumOfComponents() { return components->size(); }

private:
	std::vector<UIComponent>* components;


};

