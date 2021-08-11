#pragma once

#include <utility>

class HSceneComponent;
class SDL_Renderer;

class HActor
{
public:
    HActor() = default;
    virtual ~HActor() = default;

public:
    void moveTo(const std::pair<int, int>& loc);
    void rotateActor(float degree);
    virtual void render();
    virtual void update(float deltaTime);

public:
    void setVisibility(bool isVisible);
    const bool getVisibility();
    const HSceneComponent* getRootComponent;
    void setRootComponent(HSceneComponent* component);
    const std::pair<int, int> getActorDirectionalVector();
    const std::pair<int, int> getActorWorldLocation();
    const float getActorWorldRotation();
    void setActorTickable(bool isTickable);
    const bool getActorTickable();
    void setLifeTime(const float lifeTime);
    void setIsSetLifeTime(const bool isSetLifeTime);
    const bool getIsSetLifeTime();

protected:
    HSceneComponent* rootComponent;
    std::pair<float, float> dirVec;
    float lifeTime = 0.0f;
    bool visibility;
    bool tickable;
    bool isSetLifeTime = false;
    bool isPendingToKill = false;
};
