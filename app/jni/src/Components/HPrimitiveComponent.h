#pragma once

#include "HSceneComponent.h"


class HPrimitiveComponent: public HSceneComponent
{
public:
    HPrimitiveComponent();
    HPrimitiveComponent(const HPrimitiveComponent&) = delete;
    HPrimitiveComponent& operator=(const HPrimitiveComponent&) = delete;
    virtual ~HPrimitiveComponent();

public:
    virtual void update(const float deltaTime) override;
    virtual void render() override;

public:
    void setVisibility(bool isVisible);
    void setScale(const std::pair<int, int>& scale);
    std::pair<int, int> getScale();
    bool getVisibility();

protected:
    bool visibility = true;
    std::pair<int, int> scale = std::make_pair(1.0f, 1.0f);
};