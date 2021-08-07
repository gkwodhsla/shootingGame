#pragma once
#include "HComponent.h"
#include <utility>
#include <vector>
class HSceneComponent :public HComponent
{
public:
    HSceneComponent();
    virtual ~HSceneComponent();

public:
    void componentRotation(float degree);
    void componentMoveTo(std::pair<int, int>& location);
    void update(float deltaTime) override;
public:
    const std::pair<int, int> getComponentWorldLocation();
    const float getComponentWorldRotation();
    const std::pair<int, int> getComponentLocalLocation();
    const float getComponentLocalRotation();
    const HSceneComponent* getParentComponent();
    void attachTo();

protected:
    HSceneComponent* parent;
    std::vector<HSceneComponent*> children;
    std::pair<int, int> localLocation;
    float localRotation;
};