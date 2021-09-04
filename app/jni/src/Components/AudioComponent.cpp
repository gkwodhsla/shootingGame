#include "AudioComponent.h"
#include <SDL_mixer.h>

AudioComponent::AudioComponent(const std::string &audioPath, __uint8_t volume, HActor *owner)
{
    loadAudio(audioPath);
    this->volume = volume / 2;
    this->owner = owner;
    Mix_VolumeChunk(audio, this->volume);
}

AudioComponent::~AudioComponent()
{
    Mix_FreeChunk(audio);
    audio = nullptr;
}

void AudioComponent::update(float deltaTime)
{

}

void AudioComponent::changeVolume(__uint8_t volume)
{
    this->volume = volume / 2;
    Mix_VolumeChunk(audio, this->volume);
}

void AudioComponent::changeAudio(const std::string& audioPath)
{
    loadAudio(audioPath);
}

void AudioComponent::play()
{
    Mix_PlayChannel(-1, audio, 0);
}

void AudioComponent::loadAudio(const std::string& path)
{
    if(audio)
    {
        Mix_FreeChunk(audio);
        audio = nullptr;
    }
    audio = Mix_LoadWAV(path.c_str());
    Mix_VolumeChunk(audio, volume);
}