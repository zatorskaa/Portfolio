#include "NetworkComponent.h"
#include "NetworkSubsystem.h"
#include "GameObject.h"
#include "EventQueue.h"

NetworkComponent& NetworkComponent::operator=(const NetworkComponent& _other)
{
	if (this == &_other)
		return *this;

	NetworkComponent a(_other);
	return a;
}

void NetworkComponent::Update()
{
	//create an event for the player to copy its physics component position and rotation
	//to the network component to send to the server
	if (gameObject->GetName() == "Player")
	{
		std::vector<GameObject*> gameObjects;
		std::vector<SubsystemType> subsystemType;
		int i;

		Event* eventE = new Event();

		for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
		{
			gameObjects.push_back(subsystem->GetGameObjects()->at(i));
		}

		subsystemType.push_back(SubsystemType::Network);

		eventE->AssignObjects(gameObjects);
		eventE->AssignSubsystemType(subsystemType);
		eventE->AssignEventType(EventType::NetworkUpdate);
		subsystem->GetEventQueue()->events.push_back(eventE);
	}
}

void NetworkComponent::UpdateNetPosition()
{
	//create an event get the net object's (player 2's) position and score recieved from the server
	//and copy it from the network component to the physics and graphics components
	if (gameObject->GetName() == "NetObject")
	{
		std::vector<GameObject*> gameObjects;
		std::vector<SubsystemType> subsystemType;
		int i;

		Event* eventE = new Event();

		for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
		{
			gameObjects.push_back(subsystem->GetGameObjects()->at(i));
		}

		subsystemType.push_back(SubsystemType::Network);

		eventE->AssignObjects(gameObjects);
		eventE->AssignSubsystemType(subsystemType);
		eventE->AssignEventType(EventType::NetworkUpdateRecieved);
		subsystem->GetEventQueue()->events.push_back(eventE);
	}
}
