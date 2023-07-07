#include "AudioSubsystem.h"
#include "EventQueue.h"
#include "GameObject.h"

sf::Music AudioSubsystem::music;

Component* AudioSubsystem::AddComponent(Component* _component)
{
	if (_component->GetComponentType() == ComponentType::Audio)
	{
		AudioComponent* temp = static_cast<AudioComponent*>(_component);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Not an audio component" << std::endl;
		return nullptr;
	}
}

void AudioSubsystem::RemoveComponent(int _i)
{
	components->erase(components->begin() + _i);
}

void AudioSubsystem::Update()
{
	//update each game object
	for (int i = 0; i < components->size(); i++)
	{
		components->at(i).Update();
	}

	//check the event queue for audio events
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
					try
					{
						temp->subsystemTypes.erase(temp->subsystemTypes.begin() + j);
					}
					catch (const std::exception& e)
					{
						std::cout << "UI Error" << std::endl;
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
}

void AudioSubsystem::PlayPauseMusic()
{
	if (music.getStatus() == sf::Music::Status::Playing)
	{
		//check if the music is playing and pause if it is
		music.pause();
	}
	else if (music.getStatus() == sf::Music::Status::Paused)
	{
		//if the music is paused, resume playing it
		music.play();
	}
}
