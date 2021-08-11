#pragma once

#include "HPawn.h"

class ImageComponent;

class Airplane :public HPawn
{
public:
    Airplane();
    virtual ~Airplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;
private:
    ImageComponent* airplaneImg;
};