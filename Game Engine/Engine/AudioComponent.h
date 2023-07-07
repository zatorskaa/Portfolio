#pragma once

#include <SFML/Audio.hpp>

#include "Common.h"
#include "Component.h"

class AudioComponent : public Component
{
public:
	//constructors
	AudioComponent(GameObject* _gameObject, Subsystem* _subsystem, std::string _sound)
		: Component(ComponentType::Audio, _gameObject, _subsystem)
	{
		//load the sound effect to the sound buffer
		if (!soundBuffer.loadFromFile(_sound))
		{
			std::cout << "Sound effect did not load!" << "\n";
		}
	};

	AudioComponent& operator=(const AudioComponent& _other);

	void Update();

	void PlayShootSound();

private:
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};

