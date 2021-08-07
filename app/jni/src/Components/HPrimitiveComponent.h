#pragma once

#include "HSceneComponent.h"

class SDL_Renderer;

class HPrimitiveComponent: public HSceneComponent
{
public:
    HPrimitiveComponent();
    virtual ~HPrimitiveComponent();

public:
    virtual void update(float deltaTime) override;
    virtual void render(SDL_Renderer*);

public:
    void setVisibility(bool isVisible);
    void setScale(std::pair<float, float>& scale);
    const std::pair<float, float> getScale();
    const bool getVisibility();

protected:
    bool visibility;
    std::pair<float, float> scale = std::make_pair(1.0f, 1.0f);
};