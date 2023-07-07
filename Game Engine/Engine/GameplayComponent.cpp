#include "GameplayComponent.h"
#include "GameplaySubsystem.h"
#include "GameObject.h"
#include "EventQueue.h"

GameplayComponent& GameplayComponent::operator=(const GameplayComponent& _other)
{
	if (this == &_other)
		return *this;

	GameplayComponent a(_other);
	return a;
}

void GameplayComponent::Update()
{
	//if the object is an AI call the patrol function
	if (isAI)
	{
		Patrol();
	}
}

void GameplayComponent::Patrol()
{
	std::vector<GameObject*> gameObjects;
	std::vector<SubsystemType> subsystemType;
	int i;
	
	//check if the AI object is within range of the next waypoint
	if (position.y > (GetNextWaypoint().y - 0.1) && position.y < (GetNextWaypoint().y + 0.1)
		&& position.x >(GetNextWaypoint().x - 0.1) && position.x < (GetNextWaypoint().x + 0.1))
	{
		//set the destination to the next waypoint
		if (nextWaypoint + 1 < waypoints.size())
		{
			nextWaypoint++;
		}
		else
		{
			nextWaypoint = 0;
		}
	}

	//check the y position of the AI and create an event to move up or down
	if (!(position.y > (GetNextWaypoint().y - 0.1) && position.y < (GetNextWaypoint().y + 0.1)))
	{
		if (position.y < GetNextWaypoint().y)
		{
			Event* eventE = new Event();

			for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
			{
				gameObjects.push_back(subsystem->GetGameObjects()->at(i));
			}

			subsystemType.push_back(SubsystemType::Physics);
			subsystemType.push_back(SubsystemType::Graphics);

			eventE->AssignObjects(gameObjects);
			eventE->AssignSubsystemType(subsystemType);
			eventE->AssignEventType(EventType::PatrolUp);
			subsystem->GetEventQueue()->events.push_back(eventE);
		}
		if (position.y > GetNextWaypoint().y)
		{
			Event* eventE = new Event();

			for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
			{
				gameObjects.push_back(subsystem->GetGameObjects()->at(i));
			}

			subsystemType.push_back(SubsystemType::Physics);
			subsystemType.push_back(SubsystemType::Graphics);

			eventE->AssignObjects(gameObjects);
			eventE->AssignSubsystemType(subsystemType);
			eventE->AssignEventType(EventType::PatrolDown);
			subsystem->GetEventQueue()->events.push_back(eventE);
		}
	}

	//check the x position of the AI object and create an event to move left or right
	if (!(position.x > (GetNextWaypoint().x - 0.1) && position.x < (GetNextWaypoint().x + 0.1)))
	{
		if (position.x > GetNextWaypoint().x)
		{
			Event* eventE = new Event();

			for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
			{
				gameObjects.push_back(subsystem->GetGameObjects()->at(i));
			}

			subsystemType.push_back(SubsystemType::Physics);
			subsystemType.push_back(SubsystemType::Graphics);

			eventE->AssignObjects(gameObjects);
			eventE->AssignSubsystemType(subsystemType);
			eventE->AssignEventType(EventType::PatrolLeft);
			subsystem->GetEventQueue()->events.push_back(eventE);
		}
		if (position.x < GetNextWaypoint().x)
		{
			Event* eventE = new Event();

			for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
			{
				gameObjects.push_back(subsystem->GetGameObjects()->at(i));
			}

			subsystemType.push_back(SubsystemType::Physics);
			subsystemType.push_back(SubsystemType::Graphics);

			eventE->AssignObjects(gameObjects);
			eventE->AssignSubsystemType(subsystemType);
			eventE->AssignEventType(EventType::PatrolRight);
			subsystem->GetEventQueue()->events.push_back(eventE);
		}
	}

}
