#pragma once

#include <Box2D/Box2D.h>

#include "Common.h"
#include "Subsystem.h"
#include "PhysicsComponent.h"

class PhysicsSubsystem : public Subsystem
{
public:
	//constructors
	PhysicsSubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: Subsystem(SubsystemType::Physics, _eventQueue, _gameObjects), gravity(b2Vec2(0,0)), world(gravity)
	{
		components = new std::vector<PhysicsComponent>;
		components->reserve(MAX_ENTITIES);

		//set the box2d world time step and iterations for each frame
		timeStep = 1.0f / 60.0f;
		velocityIterations = 8;
		positionIterations = 3;
	};
	PhysicsSubsystem(const PhysicsSubsystem& _other) 
		: Subsystem(_other), gravity(b2Vec2(0, 0)), world(gravity)
	{ 
		components->reserve(MAX_ENTITIES);

		//set the box2d world time step and iterations for each frame
		timeStep = 1.0f / 60.0f;
		velocityIterations = 8;
		positionIterations = 3;
	};

	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }
	b2World* GetWorld() { return &world; }

	void Update();
	int GetNumOfComponents() { return components->size(); }

	static bool GetSpawnNetObject() { return spawnNetObject; }
	static void SetSpawnNetObject(bool _spawnNetObject) { spawnNetObject = _spawnNetObject; }

private:
	std::vector<PhysicsComponent>* components;
	b2Vec2 gravity;
	b2World world;

	float timeStep;
	int velocityIterations;
	int positionIterations;

	static bool spawnNetObject;
};

