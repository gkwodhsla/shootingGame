#pragma once

#include "HActor.h"

class ImageComponent;
class SDL_Rect;

class BackgroundActor :public HActor
{
public:
    BackgroundActor();
    virtual ~BackgroundActor();

public:
    void render() override;
    void update(float deltaTime) override;
    void changeBackgroundImage(const std::string&);
private:
    ImageComponent* backgroundImage;
    SDL_Rect* camera;
    const int cameraWidthAndHeight = 300;
    float accYPos = 0.0f;
    const float acceleration = -300.0f;
    const float velocity = -200.0f;

};