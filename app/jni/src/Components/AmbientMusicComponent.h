#pragma once
#include "HComponent.h"
#include <SDL_mixer.h>
//class Mix_Music;

class AmbientMusicComponent : public HComponent
{
public:
    AmbientMusicComponent(const std::string& musicPath, __uint8_t volume, HActor* owner);
    virtual ~AmbientMusicComponent();
    virtual void update(float deltaTime) override;
    void changeVolume(__uint8_t volume);
    void changeMusic(const std::string& musicPath);
    void play();
    void stop();
    void pause();
    void resume();

private:
    void loadMusic(const std::string& musicPath);

private:
    Mix_Music* music = nullptr;
    __uint8_t volume = 64;
};