#pragma once

#include "HComponent.h"

class Mix_Chunk;

class AudioComponent : public HComponent
{
public:
    AudioComponent(const std::string& audioPath, __uint8_t volume, HActor* owner);
    virtual ~AudioComponent();
    virtual void update(float deltaTime) override;
    void changeVolume(__uint8_t volume);
    void changeAudio(const std::string& audioPath);
    void play();

private:
    void loadAudio(const std::string& path);

private:
    Mix_Chunk* audio = nullptr;
    __uint8_t volume = 64;
};
