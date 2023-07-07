#include "PhysicsSubsystem.h"
#include "EventQueue.h"
#include "GameObject.h"

bool PhysicsSubsystem::spawnNetObject = false;

Component* PhysicsSubsystem::AddComponent(Component* _component)
{
	if (_component->GetComponentType() == ComponentType::Physics)
	{
		PhysicsComponent* temp = static_cast<PhysicsComponent*>(_component);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Not a physics component" << std::endl;
		return nullptr;
	}
}

void PhysicsSubsystem::RemoveComponent(int _i)
{
	components->erase(components->begin() + _i);
}

void PhysicsSubsystem::Update()
{
	//update each game object
	for (int i = 0; i < components->size(); i++)
	{
		if (components->at(i).GetGameObject()->GetName() == "NetObject")
		{
			//check if the network object (player 2) is enabled and call its update if it is
			if (spawnNetObject)
			{
				components->at(i).Update();
			}
		}
		else
		{
			components->at(i).Update();
		}
	}

	//check the event queue for physics events
	int eQsize = eventQueue->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			temp = eventQueue->events[i];

			for (int j = 0; j < temp->subsystemTypes.size(); j++)
			{
				if (temp->subsystemTypes[j] == subsystemType)
				{
					//check the event type and call the matching function in the event queue function map
					auto it = eventQueue->functionMap.find(subsystemType);

					auto it2 = it->second->find(temp->eventType);

					it2->second(temp);

					//after calling the function, delete the current subsystem type from the event
					try {
						temp->subsystemTypes.erase(temp->subsystemTypes.begin() + j);
					}
					catch(const std::exception& e) {
						std::cout << "Physics Error" << std::endl;
					}

					//if there are no more subsystem types in the event, delete the event fromt the event queue
					if (temp->subsystemTypes.size() == 0)
					{
						delete eventQueue->events[i];
						eventQueue->events.erase(eventQueue->events.begin() + i);
						eQsize = eventQueue->events.size();
					}
				}
			}
		}
	}

	//box2d calculates velocities and positions of objects
	world.Step(timeStep, velocityIterations, positionIterations);
}
