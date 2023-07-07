#pragma once

#include <SFML/Audio.hpp>

#include "Common.h"
#include "Subsystem.h"
#include "AudioComponent.h"

class AudioSubsystem : public Subsystem
{
public:
	//constructors
	AudioSubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects, std::string _music)
		: Subsystem(SubsystemType::Audio, _eventQueue, _gameObjects)
	{
		components = new std::vector<AudioComponent>;
		components->reserve(MAX_ENTITIES);

		//load the music
		if (!music.openFromFile(_music))
		{
			std::cout << "Music did not load!" << "\n";
		}
		else
		{
			//play the music
			music.setVolume(40);
			music.setLoop(true);
			music.play();
		}
	};
	AudioSubsystem(const AudioSubsystem& _other)
		: Subsystem(_other)
	{
		components->reserve(MAX_ENTITIES);
	};

	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }

	void Update();
	int GetNumOfComponents() { return components->size(); }

	static void PlayPauseMusic();

private:
	std::vector<AudioComponent>* components;

	static sf::Music music;
};

