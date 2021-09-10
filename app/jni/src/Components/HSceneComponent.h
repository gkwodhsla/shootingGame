#pragma once
#include "HComponent.h"
#include <utility>
#include <vector>

class HActor;

class HSceneComponent :public HComponent
{
public:
    HSceneComponent();
    HSceneComponent(const HSceneComponent&) = delete;
    HSceneComponent& operator=(const HSceneComponent&) = delete;
    virtual ~HSceneComponent();

public:
    void updateComponentWorldRotation();
    void updateComponentWorldLocation();
    virtual void render();
    void update(const float deltaTime) override;
public:
    std::pair<float, float> getComponentWorldLocation();
    float getComponentWorldRotation();
    std::pair<float, float> getComponentLocalLocation();
    float getComponentLocalRotation();
    HSceneComponent* getParentComponent();
    void setComponentLocalLocation(const std::pair<float, float>& loc);
    void setComponentLocalRotation(const float degree);
    void setOwner(HActor* owner);
    void setAffectRotationFromParent (bool isAffect);
    bool getAffectRotationFromParent ();
    void setAffectLocationFromParent (bool isAffect);
    bool getAffectLocationFromParent ();

public:
    void attachTo(HSceneComponent* component, bool isAffectFromParent = true);

protected:
    HSceneComponent* parent = nullptr;
    std::vector<HSceneComponent*> children;
    std::pair<float, float> localLocation;
    std::pair<float, float> worldLocation;
    float localRotation = 0.0f;
    float worldRotation = 0.0f;
    bool isUsingParentLocation = true;
    bool isUsingParentRotation = true;
};