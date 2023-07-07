#include "EventQueue.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "GameplayComponent.h"
#include "UIComponent.h"
#include "NetworkComponent.h"
#include "GraphicsSubsystem.h"
#include "PhysicsSubsystem.h"
#include "UISubsystem.h"
#include "GameplaySubsystem.h"
#include "NetworkSubsystem.h"
#include "AudioSubsystem.h"
#include "AudioComponent.h"

float playerSpeed = 5;
float bossSpeed = 2.5;

void PhysicsMoveUp(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player")
		{
			//get the player's physics component and call the move function to move the player up
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);

			Vector2 speed;
			speed.x = 0;
			speed.y = playerSpeed;
			tempPhysics->Move(speed);
		}
	}
}

void PhysicsMoveDown(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player")
		{
			//get the player's physics component and call the move function to move the player down
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);

			Vector2 speed;
			speed.x = 0;
			speed.y = -playerSpeed;
			tempPhysics->Move(speed);
		}
	}
}

void PhysicsMoveLeft(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player")
		{
			//get the player's physics component and call the move function to move the player left
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);

			Vector2 speed;
			speed.x = -playerSpeed;
			speed.y = 0;
			tempPhysics->Move(speed);
		}
	}
}

void PhysicsMoveRight(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player")
		{
			//get the player's physics component and call the move function to move the player right
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);

			Vector2 speed;
			speed.x = playerSpeed;
			speed.y = 0;
			tempPhysics->Move(speed);
		}
	}
}

void GraphicsMoveUp(Event* _event) 
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player" || temp->GetName() == "Boss")
		{
			//get the object's position from its physics component and pass it to the graphics component
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			GraphicsComponent* tempGraphics = static_cast<GraphicsComponent*>(ptr);

			Vector2 pos = tempPhysics->GetPosition();
			float rot = tempPhysics->GetRotation();
			tempGraphics->Move(pos, rot);
		}
	}
}

void GraphicsMoveDown(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player" || temp->GetName() == "Boss")
		{
			//get the object's position from its physics component and pass it to the graphics component
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			GraphicsComponent* tempGraphics = static_cast<GraphicsComponent*>(ptr);

			Vector2 pos = tempPhysics->GetPosition();
			float rot = tempPhysics->GetRotation();
			tempGraphics->Move(pos, rot);
		}
	}
}

void GraphicsMoveLeft(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player" || temp->GetName() == "Boss")
		{
			//get the object's position from its physics component and pass it to the graphics component
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			GraphicsComponent* tempGraphics = static_cast<GraphicsComponent*>(ptr);

			Vector2 pos = tempPhysics->GetPosition();
			float rot = tempPhysics->GetRotation();
			tempGraphics->Move(pos, rot);
		}
	}
}

void GraphicsMoveRight(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player" || temp->GetName() == "Boss")
		{
			//get the object's position from its physics component and pass it to the graphics component
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			GraphicsComponent* tempGraphics = static_cast<GraphicsComponent*>(ptr);

			Vector2 pos = tempPhysics->GetPosition();
			float rot = tempPhysics->GetRotation();
			tempGraphics->Move(pos, rot);
		}
	}
}

void PatrolUp(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Boss")
		{
			//move the AI up using the physics component
			//then pass the new position to the gameplay component to update the patrol direction
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Gameplay);
			GameplayComponent* tempGameplay = static_cast<GameplayComponent*>(ptr);

			Vector2 speed;
			speed.x = 0;
			speed.y = bossSpeed;
			tempPhysics->Move(speed);

			tempGameplay->SetPosition(tempPhysics->GetPosition());
		}
	}
}

void PatrolDown(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Boss")
		{
			//move the AI down using the physics component
			//then pass the new position to the gameplay component to update the patrol direction
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Gameplay);
			GameplayComponent* tempGameplay = static_cast<GameplayComponent*>(ptr);

			Vector2 speed;
			speed.x = 0;
			speed.y = -bossSpeed;
			tempPhysics->Move(speed);

			tempGameplay->SetPosition(tempPhysics->GetPosition());
		}
	}
}

void PatrolLeft(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Boss")
		{
			//move the AI left using the physics component
			//then pass the new position to the gameplay component to update the patrol direction
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Gameplay);
			GameplayComponent* tempGameplay = static_cast<GameplayComponent*>(ptr);

			Vector2 speed;
			speed.x = -bossSpeed;
			speed.y = 0;
			tempPhysics->Move(speed);

			tempGameplay->SetPosition(tempPhysics->GetPosition());
		}
	}
}

void PatrolRight(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Boss")
		{
			//move the AI right using the physics component
			//then pass the new position to the gameplay component to update the patrol direction
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Gameplay);
			GameplayComponent* tempGameplay = static_cast<GameplayComponent*>(ptr);

			Vector2 speed;
			speed.x = bossSpeed;
			speed.y = 0;
			tempPhysics->Move(speed);

			tempGameplay->SetPosition(tempPhysics->GetPosition());
		}
	}
}

void Shoot(Event* _event)
{
	GameplayComponent* tempGameplayBoss;
	GraphicsComponent* tempGraphicsBoss;
	UIComponent* tempUIPlayer;
	GameplayComponent* tempGameplayPlayer;
	GraphicsComponent* tempGraphicsPlayer;
	NetworkComponent* tempNetworkPlayer;
	AudioComponent* tempAudioPlayer;

	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Boss")
		{
			Component* ptr = temp->GetComponentType(ComponentType::Gameplay);
			tempGameplayBoss = static_cast<GameplayComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			tempGraphicsBoss = static_cast<GraphicsComponent*>(ptr);

			for (int j = 0; j < _event->gameObjects.size(); j++)
			{
				GameObject* temp2 = _event->gameObjects[j];

				if (temp2->GetName() == "Player")
				{
					Component* ptr2 = temp2->GetComponentType(ComponentType::UI);
					tempUIPlayer = static_cast<UIComponent*>(ptr2);
					ptr2 = temp2->GetComponentType(ComponentType::Gameplay);
					tempGameplayPlayer = static_cast<GameplayComponent*>(ptr2);
					ptr2 = temp2->GetComponentType(ComponentType::Graphics);
					tempGraphicsPlayer = static_cast<GraphicsComponent*>(ptr2);
					ptr2 = temp2->GetComponentType(ComponentType::Network);
					tempNetworkPlayer = static_cast<NetworkComponent*>(ptr2);
					ptr2 = temp2->GetComponentType(ComponentType::Audio);
					tempAudioPlayer = static_cast<AudioComponent*>(ptr2);

					//check if the mouse position is within the graphics bounds of the boss object when the mouse is pressed
					if (tempUIPlayer->GetMousePos().x < tempGraphicsBoss->GetPosition().x + tempGraphicsBoss->GetHalfSize().x
						&& tempUIPlayer->GetMousePos().x > tempGraphicsBoss->GetPosition().x - tempGraphicsBoss->GetHalfSize().x
						&& tempUIPlayer->GetMousePos().y < tempGraphicsBoss->GetPosition().y + tempGraphicsBoss->GetHalfSize().y
						&& tempUIPlayer->GetMousePos().y > tempGraphicsBoss->GetPosition().y - tempGraphicsBoss->GetHalfSize().y)
					{
						//decrease the boss's health and increase the player's score
						//then pass the new score to the graphics component to display it
						//and to the network component to send it to the other player
						//play a shooting sound in the player's audio component
						tempGameplayBoss->SetHealth(tempGameplayBoss->GetHealth() - 1);
						tempGameplayPlayer->AddScore(10);
						tempGraphicsPlayer->SetScore(tempGameplayPlayer->GetScore());
						tempNetworkPlayer->SetScore(tempGameplayPlayer->GetScore());
						tempAudioPlayer->PlayShootSound();

						std::cout << "Boss Health:" << tempGameplayBoss->GetHealth() << std::endl;

					}
				}
			}
		}

	}
}

void UpdateNetworkPositions(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "Player")
		{
			//pass the player's physics postion and rotation to the network to send to the other player
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Network);
			NetworkComponent* tempNetwork = static_cast<NetworkComponent*>(ptr);

			tempNetwork->SetPosition(tempPhysics->GetPosition());
			tempNetwork->SetRotation(tempPhysics->GetRotation());
		}
	}
}

void UpdateNetworkPositionsRecieved(Event* _event)
{
	for (int i = 0; i < _event->gameObjects.size(); i++)
	{
		GameObject* temp = _event->gameObjects[i];

		if (temp->GetName() == "NetObject")
		{
			//get the other player's position from the network component and pass it to the physics and graphics componments
			Component* ptr = temp->GetComponentType(ComponentType::Physics);
			PhysicsComponent* tempPhysics = static_cast<PhysicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Network);
			NetworkComponent* tempNetwork = static_cast<NetworkComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Graphics);
			GraphicsComponent* tempGraphics = static_cast<GraphicsComponent*>(ptr);
			ptr = temp->GetComponentType(ComponentType::Gameplay);
			GameplayComponent* tempGameplay = static_cast<GameplayComponent*>(ptr);

			tempPhysics->SetTransform(tempNetwork->GetPosition(), tempNetwork->GetRotation());
			tempGraphics->Move(tempNetwork->GetPosition(), tempNetwork->GetRotation());

			tempGameplay->SetScore(tempNetwork->GetScore());
			tempGraphics->SetScore(tempNetwork->GetScore());
		}
	}
}

void SpawnNetworkObject(Event* _event)
{
	//enable the network game object in all subsystems if the player is connected to a server with another player
	GameplaySubsystem::SetSpawnNetObject(true);
	GraphicsSubsystem::SetSpawnNetObject(true);
	PhysicsSubsystem::SetSpawnNetObject(true);
}

void PlayMusic(Event* _event)
{
	//play or pause the music
	AudioSubsystem::PlayPauseMusic();
}


void EventQueue::InitialiseFunctionMaps()
{
	//physics
	std::unordered_map<EventType, void(*)(Event*)>* physicsMap = new std::unordered_map<EventType, void(*)(Event*)>;

	//map physics event types to physics functions
	physicsMap->insert({ EventType::MoveUp, &PhysicsMoveUp });
	physicsMap->insert({ EventType::MoveDown, &PhysicsMoveDown });
	physicsMap->insert({ EventType::MoveLeft, &PhysicsMoveLeft });
	physicsMap->insert({ EventType::MoveRight, &PhysicsMoveRight });
	physicsMap->insert({ EventType::PatrolUp, &PatrolUp });
	physicsMap->insert({ EventType::PatrolDown, &PatrolDown });
	physicsMap->insert({ EventType::PatrolLeft, &PatrolLeft });
	physicsMap->insert({ EventType::PatrolRight, &PatrolRight });

	functionMaps.push_back(physicsMap);
	functionMap.insert({ SubsystemType::Physics, physicsMap });


	//graphics
	std::unordered_map<EventType, void(*)(Event*)>* graphicsMap = new std::unordered_map<EventType, void(*)(Event*)>;

	//map graphics events to graphics functions
	graphicsMap->insert({ EventType::MoveUp, &GraphicsMoveUp });
	graphicsMap->insert({ EventType::MoveDown, &GraphicsMoveDown });
	graphicsMap->insert({ EventType::MoveLeft, &GraphicsMoveLeft });
	graphicsMap->insert({ EventType::MoveRight, &GraphicsMoveRight });
	graphicsMap->insert({ EventType::PatrolUp, &GraphicsMoveUp });
	graphicsMap->insert({ EventType::PatrolDown, &GraphicsMoveDown });
	graphicsMap->insert({ EventType::PatrolLeft, &GraphicsMoveLeft });
	graphicsMap->insert({ EventType::PatrolRight, &GraphicsMoveRight });

	functionMaps.push_back(graphicsMap);
	functionMap.insert({ SubsystemType::Graphics, graphicsMap });


	//gameplay
	std::unordered_map<EventType, void(*)(Event*)>* gameplayMap = new std::unordered_map<EventType, void(*)(Event*)>;

	gameplayMap->insert({ EventType::Shoot, &Shoot });

	//map gameplay events to gameplay functions
	functionMaps.push_back(gameplayMap);
	functionMap.insert({ SubsystemType::Gameplay, gameplayMap });


	//network
	std::unordered_map<EventType, void(*)(Event*)>* networkMap = new std::unordered_map<EventType, void(*)(Event*)>;

	//map network events to network functions
	networkMap->insert({ EventType::NetworkUpdate, &UpdateNetworkPositions });
	networkMap->insert({ EventType::NetworkUpdateRecieved, &UpdateNetworkPositionsRecieved });
	networkMap->insert({ EventType::SpawnNetObject, &SpawnNetworkObject });

	functionMaps.push_back(networkMap);
	functionMap.insert({ SubsystemType::Network, networkMap });


	//audio
	std::unordered_map<EventType, void(*)(Event*)>* audioMap = new std::unordered_map<EventType, void(*)(Event*)>;

	//map network events to network functions
	audioMap->insert({ EventType::PlayMusic, &PlayMusic });

	functionMaps.push_back(audioMap);
	functionMap.insert({ SubsystemType::Audio, audioMap });
}

void EventQueue::popEvent(Event* event_)
{
	//delete events from the event queue
	for (int i = 0; i < events.size(); i++)
	{
		if (events[i] == event_)
		{
			delete events[i];
			events.erase(events.begin() + i);
		}
	}
}