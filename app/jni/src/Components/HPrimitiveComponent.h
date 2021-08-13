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
    virtual void render() override;

public:
    void setVisibility(bool isVisible);
    void setScale(const std::pair<int, int>& scale);
    std::pair<int, int> getScale();
    bool getVisibility();

protected:
    bool visibility;
    std::pair<int, int> scale = std::make_pair(1.0f, 1.0f);
};