#include "GameEngine.h"
#include "GameObject.h"
#include "GraphicsSubsystem.h"
#include "PhysicsSubsystem.h"
#include "UISubsystem.h"
#include "GameplaySubsystem.h"
#include "NetworkSubsystem.h"
#include "AudioSubsystem.h"
#include "EventQueue.h"

GameEngine::GameEngine()
{
	FileReading();

	//get the music file name from the json file
	std::string musicFile = fileData["Audio"]["Music"].asString();

	//create new pointers for event queue & for vectors
	eventQueue = new EventQueue();
	subsystems = new std::vector<Subsystem*>;
	gameObjects = new std::vector<GameObject*>;

	//reserve vectors in memory
	subsystems->reserve(6);
	gameObjects->reserve(MAX_ENTITIES);

	//create new pointers for subsystems
	graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);
	physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	uiSubsystem = new UISubsystem(eventQueue, gameObjects);
	gameplaySubsystem = new GameplaySubsystem(eventQueue, gameObjects);
	networkSubsystem = new NetworkSubsystem(eventQueue, gameObjects);
	audioSubsystem = new AudioSubsystem(eventQueue, gameObjects, musicFile);

	//add subsystem pointers to vector
	subsystems->push_back(uiSubsystem);
	subsystems->push_back(gameplaySubsystem);
	subsystems->push_back(physicsSubsystem);
	subsystems->push_back(graphicsSubsystem);
	subsystems->push_back(networkSubsystem);
	subsystems->push_back(audioSubsystem);

	//call function to create game objects
	SetUp();
}

GameEngine::~GameEngine()
{
	//delete pointers
	int i;

	for (i = 0; i < subsystems->size(); i++)
	{
		delete subsystems->at(i);
	}

	for (i = 0; i < gameObjects->size(); i++)
	{
		delete gameObjects->at(i);
	}

	delete subsystems;
	delete gameObjects;
	delete eventQueue;
}

int GameEngine::Update()
{
	//update each subsystem
	int i;
	for (i = 0; i < subsystems->size(); i++)
	{
		subsystems->at(i)->Update();
	}

	//check for exit event and stop running the game engine
	int eQSize = eventQueue->events.size();

	if (eQSize > 0)
	{
		for (i = 0; i < eQSize; i++)
		{
			if (eventQueue->events[i]->eventType == EventType::Exit)
			{
				return false;
			}

			if (eventQueue->events[i]->subsystemTypes.size() == 0)
			{
				delete eventQueue->events[i];
				eventQueue->events.erase(eventQueue->events.begin() + i);
				eQSize = eventQueue->events.size();
			}
		}
	}

	return true;
}

void GameEngine::FileReading()
{
	//read the json data file for the level
	std::ifstream file("data.json");
	file >> fileData;
	file.close();
}

void GameEngine::SetUp()
{
	//get data for the player object from the json file
	int playerHealth = fileData["Player"]["Health"].asInt();
	Vector2 playerPos = Vector2(fileData["Player"]["PosX"].asFloat(), fileData["Player"]["PosY"].asFloat());
	Vector2 playerSize = Vector2(fileData["Player"]["SizeX"].asFloat(), fileData["Player"]["SizeY"].asFloat());
	std::string playerTexture = fileData["Player"]["Texture"].asString();
	std::string playerSound = fileData["Player"]["Sound"].asString();

	/*
	* create game objects and components for each object
	* 
	* each object has a gameplay component for game logic,
	* a physics componet for movement & collisions,
	* and a graphics component to render the object on screen
	*/

	//Player - dynamic object that the player controls
	gameObjects->push_back(new GameObject("Player"));

	/*
	* create components for player
	* 
	* this object also has a ui component so the player can control it,
	* and a network component so it can send data to the server
	*/
	UIComponent playerUI(gameObjects->back(), subsystems->at(0), graphicsSubsystem->GetWindow());
	GameplayComponent playerGameplay(gameObjects->back(), subsystems->at(1), playerPos, playerHealth);
	PhysicsComponent playerPhysics(gameObjects->back(), subsystems->at(2), playerPos, physicsSubsystem->GetWorld(), playerSize, true);
	GraphicsComponent playerGraphics(gameObjects->back(), subsystems->at(3), playerPos, graphicsSubsystem->GetWindow(), playerSize, playerTexture);
	NetworkComponent playerNetwork(gameObjects->back(), subsystems->at(4), playerPos, true);
	AudioComponent playerAudio(gameObjects->back(), subsystems->at(5), playerSound);

	//assign the components to player
	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&playerUI));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&playerGameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&playerPhysics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&playerGraphics));
	gameObjects->back()->AddComponent(subsystems->at(4)->AddComponent(&playerNetwork));
	gameObjects->back()->AddComponent(subsystems->at(5)->AddComponent(&playerAudio));


	//get data for the boss object from the json file
	int bossHealth = fileData["Boss"]["Health"].asInt();
	Vector2 bossPos = Vector2(fileData["Boss"]["PosX"].asFloat(), fileData["Boss"]["PosY"].asFloat());
	Vector2 bossSize = Vector2(fileData["Boss"]["SizeX"].asFloat(), fileData["Boss"]["SizeY"].asFloat());
	std::string bossTexture = fileData["Boss"]["Texture"].asString();

	Json::Value waypoints = fileData["Boss"]["Waypoints"];
	std::vector<Vector2> bossWaypoints; //waypoints for the boss to move between

	for (int i = 0; i < waypoints.size(); i++)
	{
		bossWaypoints.push_back(Vector2(waypoints[i][0].asFloat(), waypoints[i][1].asFloat()));
	}

	//Boss - dynamic AI enemy object that the player needs to defeat
	gameObjects->push_back(new GameObject("Boss"));

	//create components for boss - gameplay, graphics & physics
	GameplayComponent bossGameplay(gameObjects->back(), subsystems->at(1), bossPos, bossHealth, true, bossWaypoints);
	PhysicsComponent bossPhysics(gameObjects->back(), subsystems->at(2), bossPos, physicsSubsystem->GetWorld(), bossSize, true);
	GraphicsComponent bossGraphics(gameObjects->back(), subsystems->at(3), bossPos, graphicsSubsystem->GetWindow(), bossSize, bossTexture);

	//assign the components to boss
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&bossGameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&bossPhysics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&bossGraphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle1Pos = Vector2(fileData["Obstacle1"]["PosX"].asFloat(), fileData["Obstacle1"]["PosY"].asFloat());
	Vector2 obstacle1Size = Vector2(fileData["Obstacle1"]["SizeX"].asFloat(), fileData["Obstacle1"]["SizeY"].asFloat());
	std::string obstacle1Texture = fileData["Obstacle1"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle1"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacleGameplay(gameObjects->back(), subsystems->at(1), obstacle1Pos);
	PhysicsComponent obstaclePhysics(gameObjects->back(), subsystems->at(2), obstacle1Pos, physicsSubsystem->GetWorld(), obstacle1Size, false);
	GraphicsComponent obstacleGraphics(gameObjects->back(), subsystems->at(3), obstacle1Pos, graphicsSubsystem->GetWindow(), obstacle1Size, obstacle1Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacleGameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstaclePhysics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacleGraphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle2Pos = Vector2(fileData["Obstacle2"]["PosX"].asFloat(), fileData["Obstacle2"]["PosY"].asFloat());
	Vector2 obstacle2Size = Vector2(fileData["Obstacle2"]["SizeX"].asFloat(), fileData["Obstacle2"]["SizeY"].asFloat());
	std::string obstacle2Texture = fileData["Obstacle2"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle2"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacle2Gameplay(gameObjects->back(), subsystems->at(1), obstacle2Pos);
	PhysicsComponent obstacle2Physics(gameObjects->back(), subsystems->at(2), obstacle2Pos, physicsSubsystem->GetWorld(), obstacle2Size, false);
	GraphicsComponent obstacle2Graphics(gameObjects->back(), subsystems->at(3), obstacle2Pos, graphicsSubsystem->GetWindow(), obstacle2Size, obstacle2Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacle2Gameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstacle2Physics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacle2Graphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle3Pos = Vector2(fileData["Obstacle3"]["PosX"].asFloat(), fileData["Obstacle3"]["PosY"].asFloat());
	Vector2 obstacle3Size = Vector2(fileData["Obstacle3"]["SizeX"].asFloat(), fileData["Obstacle3"]["SizeY"].asFloat());
	std::string obstacle3Texture = fileData["Obstacle3"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle3"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacle3Gameplay(gameObjects->back(), subsystems->at(1), obstacle3Pos);
	PhysicsComponent obstacle3Physics(gameObjects->back(), subsystems->at(2), obstacle3Pos, physicsSubsystem->GetWorld(), obstacle3Size, false);
	GraphicsComponent obstacle3Graphics(gameObjects->back(), subsystems->at(3), obstacle3Pos, graphicsSubsystem->GetWindow(), obstacle3Size, obstacle3Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacle3Gameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstacle3Physics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacle3Graphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle4Pos = Vector2(fileData["Obstacle4"]["PosX"].asFloat(), fileData["Obstacle4"]["PosY"].asFloat());
	Vector2 obstacle4Size = Vector2(fileData["Obstacle4"]["SizeX"].asFloat(), fileData["Obstacle4"]["SizeY"].asFloat());
	std::string obstacle4Texture = fileData["Obstacle4"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle4"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacle4Gameplay(gameObjects->back(), subsystems->at(1), obstacle4Pos);
	PhysicsComponent obstacle4Physics(gameObjects->back(), subsystems->at(2), obstacle4Pos, physicsSubsystem->GetWorld(), obstacle4Size, false);
	GraphicsComponent obstacle4Graphics(gameObjects->back(), subsystems->at(3), obstacle4Pos, graphicsSubsystem->GetWindow(), obstacle4Size, obstacle4Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacle4Gameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstacle4Physics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacle4Graphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle5Pos = Vector2(fileData["Obstacle5"]["PosX"].asFloat(), fileData["Obstacle5"]["PosY"].asFloat());
	Vector2 obstacle5Size = Vector2(fileData["Obstacle5"]["SizeX"].asFloat(), fileData["Obstacle5"]["SizeY"].asFloat());
	std::string obstacle5Texture = fileData["Obstacle5"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle5"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacle5Gameplay(gameObjects->back(), subsystems->at(1), obstacle5Pos);
	PhysicsComponent obstacle5Physics(gameObjects->back(), subsystems->at(2), obstacle5Pos, physicsSubsystem->GetWorld(), obstacle5Size, false);
	GraphicsComponent obstacle5Graphics(gameObjects->back(), subsystems->at(3), obstacle5Pos, graphicsSubsystem->GetWindow(), obstacle5Size, obstacle5Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacle5Gameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstacle5Physics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacle5Graphics));


	//get data for the obstacle object from the json file
	Vector2 obstacle6Pos = Vector2(fileData["Obstacle6"]["PosX"].asFloat(), fileData["Obstacle6"]["PosY"].asFloat());
	Vector2 obstacle6Size = Vector2(fileData["Obstacle6"]["SizeX"].asFloat(), fileData["Obstacle6"]["SizeY"].asFloat());
	std::string obstacle6Texture = fileData["Obstacle6"]["Texture"].asString();

	//Obstacle 1 - static object in level
	gameObjects->push_back(new GameObject("Obstacle6"));

	//create components for obstacle - gameplay, graphics & physics
	GameplayComponent obstacle6Gameplay(gameObjects->back(), subsystems->at(1), obstacle6Pos);
	PhysicsComponent obstacle6Physics(gameObjects->back(), subsystems->at(2), obstacle6Pos, physicsSubsystem->GetWorld(), obstacle6Size, false);
	GraphicsComponent obstacle6Graphics(gameObjects->back(), subsystems->at(3), obstacle6Pos, graphicsSubsystem->GetWindow(), obstacle6Size, obstacle6Texture);

	//assign the components to obstacle1
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&obstacle6Gameplay));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&obstacle6Physics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&obstacle6Graphics));


	AddNetworkObject();
}

void GameEngine::AddNetworkObject()
{
	//get data for the net object from the json file
	int netHealth = fileData["NetObject"]["Health"].asInt();
	Vector2 netPos = Vector2(fileData["NetObject"]["PosX"].asFloat(), fileData["NetObject"]["PosY"].asFloat());
	Vector2 netSize = Vector2(fileData["NetObject"]["SizeX"].asFloat(), fileData["NetObject"]["SizeY"].asFloat());
	std::string netTexture = fileData["NetObject"]["Texture"].asString();

	//NetObject - network object that is created when another player joins the game on the network
	gameObjects->push_back(new GameObject("NetObject"));

	/*
	* create components for net object
	*
	* this object also has a network component so it can receive data from the server
	*/
	GameplayComponent playerGameplay2(gameObjects->back(), subsystems->at(1), netPos, netHealth);
	PhysicsComponent playerPhysics2(gameObjects->back(), subsystems->at(2), netPos, physicsSubsystem->GetWorld(), netSize, true);
	GraphicsComponent playerGraphics2(gameObjects->back(), subsystems->at(3), netPos, graphicsSubsystem->GetWindow(), netSize, netTexture);
	NetworkComponent playerNetwork2(gameObjects->back(), subsystems->at(4), netPos, false);

	//assign the components to net object
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&playerGameplay2));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&playerPhysics2));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&playerGraphics2));
	gameObjects->back()->AddComponent(subsystems->at(4)->AddComponent(&playerNetwork2));
}
