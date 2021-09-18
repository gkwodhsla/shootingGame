#pragma once

#include "HComponent.h"
//효과음에 사용되는 컴포넌트로 .wav 파일을 사용한다.
class Mix_Chunk;

class AudioComponent : public HComponent
{
public:
    AudioComponent(const std::string& audioPath, __uint8_t volume, HActor* owner);
    AudioComponent(const AudioComponent&) = delete;
    AudioComponent& operator=(const AudioComponent&) = delete;
    virtual ~AudioComponent();
    virtual void update(const float deltaTime) override;
    void changeVolume(__uint8_t volume);
    void changeAudio(const std::string& audioPath);
    void play();

private:
    void loadAudio(const std::string& path);

private:
    Mix_Chunk* audio = nullptr;
    __uint8_t volume = 64;
};
