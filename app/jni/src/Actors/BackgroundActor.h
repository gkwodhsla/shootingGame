#pragma once

#include "HActor.h"

class ImageComponent;
class SDL_Rect;
class AmbientMusicComponent;

class BackgroundActor :public HActor
{
public:
    BackgroundActor();
    BackgroundActor(const BackgroundActor&) = delete;
    BackgroundActor& operator=(const BackgroundActor&) = delete;
    virtual ~BackgroundActor();

public:
    void render() override;
    void update(const float deltaTime) override;
    void changeBackgroundImage(const std::string&);
    void playBattleMusic();
    void stopBattleMusic();
private:
    ImageComponent* backgroundImage = nullptr;
    AmbientMusicComponent* battleMusic = nullptr;
    AmbientMusicComponent* shopMusic = nullptr;
    SDL_Rect* camera = nullptr;
    const int cameraWidthAndHeight = 300;
    float accYPos = 0.0f;
    const float acceleration = -300.0f;
    const float velocity = -200.0f;

};