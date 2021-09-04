#include "AmbientMusicComponent.h"


AmbientMusicComponent::AmbientMusicComponent(const std::string &musicPath, __uint8_t volume, HActor *owner)
{
    loadMusic(musicPath);
    this->owner = owner;
    this->volume = volume / 2;
    Mix_VolumeMusic(this->volume);
}

AmbientMusicComponent::~AmbientMusicComponent()
{
    Mix_FreeMusic(music);
    music = nullptr;
}

void AmbientMusicComponent::update(float deltaTime)
{

}

void AmbientMusicComponent::changeVolume(__uint8_t volume)
{
    this->volume = volume / 2;
    Mix_VolumeMusic(this->volume);
}

void AmbientMusicComponent::changeMusic(const std::string &musicPath)
{
    loadMusic(musicPath);
}

void AmbientMusicComponent::play()
{
    Mix_PlayMusic(music, -1);
}

void AmbientMusicComponent::stop()
{
    Mix_HaltMusic();
}


void AmbientMusicComponent::pause()
{
    Mix_PauseMusic();
}

void AmbientMusicComponent::resume()
{
    Mix_ResumeMusic();
}


void AmbientMusicComponent::loadMusic(const std::string &musicPath)
{
    if(music)
    {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    music = Mix_LoadMUS(musicPath.c_str());
}
