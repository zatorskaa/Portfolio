#include "AudioComponent.h"

AudioComponent& AudioComponent::operator=(const AudioComponent& _other)
{
	if (this == &_other)
		return *this;

	AudioComponent a(_other);
	return a;
}

void AudioComponent::Update()
{
}

void AudioComponent::PlayShootSound()
{
	//load the sound buffer and play the sound effect
	sound.setBuffer(soundBuffer);
	sound.setVolume(40);
	sound.play();
}

