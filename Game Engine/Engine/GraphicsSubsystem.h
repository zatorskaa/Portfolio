#pragma once

#include <SFML\Graphics.hpp>

#include "Common.h"
#include "Subsystem.h"
#include "GraphicsComponent.h"

class GraphicsSubsystem : public Subsystem
{
public:
	//constructors
	GraphicsSubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: Subsystem(SubsystemType::Graphics, _eventQueue, _gameObjects), windowSize(sf::Vector2f(1000, 1000)), frameLimit(60)
	{
		components = new std::vector<GraphicsComponent>;
		components->reserve(MAX_ENTITIES);

		OpenWindow(); //create a window when the graphics subsystem is created
	};
	GraphicsSubsystem(const GraphicsSubsystem& _other)
		: Subsystem(_other), windowSize(sf::Vector2f(1000, 1000)), frameLimit(60)
	{
		components->reserve(MAX_ENTITIES);
	};

	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }

	void Update();
	int GetNumOfComponents() { return components->size(); }

	sf::RenderWindow* GetWindow() { return &window; }

	static bool GetSpawnNetObject() { return spawnNetObject; }
	static void SetSpawnNetObject(bool _spawnNetObject) { spawnNetObject = _spawnNetObject; }

private:
	std::vector<GraphicsComponent>* components;

	sf::RenderWindow window;
	sf::Vector2f windowSize;
	float frameLimit;

	static bool spawnNetObject;

	void OpenWindow();
	void ClearWindow();
	void DisplayWindow();
};

