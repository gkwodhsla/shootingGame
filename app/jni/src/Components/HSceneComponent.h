#pragma once
#include "HComponent.h"
#include <utility>
#include <vector>

class HActor;

class HSceneComponent :public HComponent
{
public:
    HSceneComponent();
    virtual ~HSceneComponent();

public:
    void updateComponentWorldRotation();
    void updateComponentWorldLocation();
    virtual void render();
    void update(float deltaTime) override;
public:
    const std::pair<float, float> getComponentWorldLocation();
    const float getComponentWorldRotation();
    const std::pair<float, float> getComponentLocalLocation();
    const float getComponentLocalRotation();
    const HSceneComponent* getParentComponent();
    void setComponentLocalLocation(const std::pair<float, float>& loc);
    void setComponentLocalRotation(const float degree);
    void setOwner(HActor* owner);

public:
    void attachTo(HSceneComponent* component);

protected:
    HSceneComponent* parent;
    std::vector<HSceneComponent*> children;
    std::pair<float, float> localLocation;
    std::pair<float, float> worldLocation;
    float localRotation;
    float worldRotation;
};