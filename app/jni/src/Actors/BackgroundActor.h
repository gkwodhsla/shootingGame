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
    int yOffset = 0;
};