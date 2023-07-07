#pragma once

#include "Common.h"
#include <jsoncpp/json/json.h>

class Subsystem;
class GraphicsSubsystem;
class PhysicsSubsystem;
class UISubsystem;
class GameplaySubsystem;
class NetworkSubsystem;
class AudioSubsystem;
class EventQueue;
class GameObject;

class GameEngine
{
public:
	//constructor/destructor
	GameEngine();
	~GameEngine();

	//functions
	int Update();

private:
	std::vector<Subsystem*>* subsystems; //vector pointer of all subsystems
	std::vector<GameObject*>* gameObjects; //vector pointer of all game objects
	EventQueue* eventQueue; //pointer to event queue

	//pointers to each subsystem
	GraphicsSubsystem* graphicsSubsystem;
	PhysicsSubsystem* physicsSubsystem;
	UISubsystem* uiSubsystem;
	GameplaySubsystem* gameplaySubsystem;
	NetworkSubsystem* networkSubsystem;
	AudioSubsystem* audioSubsystem;

	//file reading
	std::ifstream file;
	Json::Value fileData;

	//functions
	void FileReading();
	void SetUp();
	void AddNetworkObject();
};

