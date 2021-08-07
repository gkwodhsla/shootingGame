#pragma once

#include "HSceneComponent.h"

class SDL_Renderer;

class HPrimitveComponent: public HSceneComponent
{
public:
    HPrimitveComponent();
    virtual ~HPrimitveComponent();

public:
    void update(float deltaTime) override;
    void Render(SDL_Renderer*);

public:
    void setVisibility(bool isVisible);
    bool getVisibility();

protected:
    bool visibility;
};