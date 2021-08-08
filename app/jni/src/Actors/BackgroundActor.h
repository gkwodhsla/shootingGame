#pragma once

#include "HActor.h"

class ImageComponent;

class BackgroundActor :public HActor
{
public:
    BackgroundActor();
    virtual ~BackgroundActor();

public:
    void render();
    void update();
    void changeBackgroundImage(const std::string&);
private:
    ImageComponent* backgroundImage;
};