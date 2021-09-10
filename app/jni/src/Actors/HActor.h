#pragma once

#include <utility>
#include <functional>
#include "../Vector2D.h"
#include "../HObject.h"

class HSceneComponent;
class SDL_Renderer;

class HActor: public HObject
{
public:
    HActor();
    HActor(const HActor&) = delete;
    HActor&operator=(const HActor&) = delete;
    virtual ~HActor() = 0;

public:
    void moveTo(const std::pair<int, int>& loc);
    void rotateActor(const float degree);
    virtual void render();
    virtual void update(const float deltaTime);

public:
    void setVisibility(const bool isVisible);
    bool getVisibility();
    HSceneComponent* getRootComponent();
    void setRootComponent(HSceneComponent* component);
    Vector2D getActorDirectionalVector();
    void setActorDirectionalVector(const Vector2D& newDir);
    std::pair<int, int> getActorWorldLocation();
    float getActorWorldRotation();
    void setActorTickable(const bool isTickable);
    bool getActorTickable();
    void setLifeTime(const float lifeTime);
    void setIsSetLifeTime(const bool isSetLifeTime);
    void registerFuncWhenActorLifeTimeZero(std::function<void()> func);
    bool getIsSetLifeTime();

protected:
    HSceneComponent* rootComponent;
    Vector2D dirVec;
    float lifeTime = 0.0f;
    bool visibility = true;
    bool tickable = true;
    bool isSetLifeTime = false;

protected:
    std::function<void()> destroyAction;
};
