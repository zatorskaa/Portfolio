#include "GraphicsSubsystem.h"
#include "EventQueue.h"
#include "GameObject.h"

bool GraphicsSubsystem::spawnNetObject = false;

Component* GraphicsSubsystem::AddComponent(Component* _component)
{
	if (_component->GetComponentType() == ComponentType::Graphics)
	{
		GraphicsComponent* temp = static_cast<GraphicsComponent*>(_component);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Not a graphics component" << std::endl;
		return nullptr;
	}
}

void GraphicsSubsystem::RemoveComponent(int _i)
{
	components->erase(components->begin() + _i);
}

void GraphicsSubsystem::Update()
{
	ClearWindow();

	//update each graphics component
	for (int i = 0; i < components->size(); i++)
	{
		if (components->at(i).GetGameObject()->GetName() == "NetObject")
		{
			//check if the network object (player 2) is enabled and call its update if it is
			if (spawnNetObject)
			{
				components->at(i).Update();
				components->at(i).DrawText();
			}
		}
		else
		{
			components->at(i).Update();
			components->at(i).DrawText();
		}
	}

	//check the event queue for graphics events
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
					//check the event type and call the matching function in the event queue
					auto it = eventQueue->functionMap.find(subsystemType);

					auto it2 = it->second->find(temp->eventType);

					it2->second(temp);

					try {
						temp->subsystemTypes.erase(temp->subsystemTypes.begin() + j);
					}
					catch (const std::exception& e) {
						std::cout << "Graphics Error" << std::endl;
					}
					
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

	DisplayWindow();
}

void GraphicsSubsystem::OpenWindow()
{
	//create an sfml window
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Game");
	window.setFramerateLimit(frameLimit);
}

void GraphicsSubsystem::ClearWindow()
{
	//clear everything from the window for each new frame
	window.clear();
}

void GraphicsSubsystem::DisplayWindow()
{
	//display all objects drawn on the window
	window.display();
}