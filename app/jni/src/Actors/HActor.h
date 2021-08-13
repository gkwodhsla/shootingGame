#pragma once

#include <utility>

class HSceneComponent;
class SDL_Renderer;

class HActor
{
public:
    HActor() = default;
    virtual ~HActor() = 0;

public:
    void moveTo(const std::pair<int, int>& loc);
    void rotateActor(const float degree);
    virtual void render();
    virtual void update(float deltaTime);

public:
    void setVisibility(const bool isVisible);
    bool getVisibility();
    HSceneComponent* getRootComponent();
    void setRootComponent(HSceneComponent* component);
    std::pair<float, float> getActorDirectionalVector();
    std::pair<int, int> getActorWorldLocation();
    float getActorWorldRotation();
    void setActorTickable(const bool isTickable);
    bool getActorTickable();
    void setLifeTime(const float lifeTime);
    void setIsSetLifeTime(const bool isSetLifeTime);
    bool getIsSetLifeTime();

protected:
    HSceneComponent* rootComponent;
    std::pair<float, float> dirVec;
    float lifeTime = 0.0f;
    bool visibility = true;
    bool tickable = true;
    bool isSetLifeTime = false;
    bool isPendingToKill = false;
};
