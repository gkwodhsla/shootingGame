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
    std::pair<float, float> getComponentWorldLocation();
    float getComponentWorldRotation();
    std::pair<float, float> getComponentLocalLocation();
    float getComponentLocalRotation();
    HSceneComponent* getParentComponent();
    void setComponentLocalLocation(const std::pair<float, float>& loc);
    void setComponentLocalRotation(const float degree);
    void setOwner(HActor* owner);

public:
    void attachTo(HSceneComponent* component);

protected:
    HSceneComponent* parent = nullptr;
    std::vector<HSceneComponent*> children;
    std::pair<float, float> localLocation;
    std::pair<float, float> worldLocation;
    float localRotation;
    float worldRotation;
};