#include "HActor.h"
#include "../Components/HSceneComponent.h"
#include "../Level/HLevelBase.h"
#include "GlobalFunction.h"
#include <cmath>
#include <android/log.h>
#include <SDL.h>

using namespace GlobalFunction;

HActor::HActor()
{
    rootComponent = new HSceneComponent();
    destroyAction = [this]()
    {
        GetLevel()->destroyActor(this);
    };
}

HActor::~HActor()
{
    delete rootComponent;
    rootComponent = nullptr;
    for(auto& component : actorComponents)
    {
        if(component)
        {
            delete component;
            component = nullptr;
        }
    }
}

void HActor::moveTo(const std::pair<int, int> &loc)
{
    rootComponent->setComponentLocalLocation(loc);
}

void HActor::rotateActor(const float degree)
{
    rootComponent->setComponentLocalRotation(degree);
}

void HActor::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

bool HActor::getVisibility()
{
    return visibility;
}

HSceneComponent* HActor::getRootComponent()
{
    return rootComponent;
}

Vector2D HActor::getActorDirectionalVector()
{
    return dirVec;
}

void HActor::setActorDirectionalVector(const Vector2D& newDir)
{
    dirVec = newDir;
}


std::pair<int, int> HActor::getActorWorldLocation()
{
    return rootComponent->getComponentLocalLocation();
}

float HActor::getActorWorldRotation()
{
    return rootComponent->getComponentLocalRotation();
}

void HActor::setActorTickable(const bool isTickable)
{
    tickable = isTickable;
}

bool HActor::getActorTickable()
{
    return tickable;
}

void HActor::render()
{
    if(visibility)
    {
        rootComponent->render();
    }

}

void HActor::update(const float deltaTime)
{
    if(tickable)
    {
        rootComponent->update(deltaTime);

        if (isSetLifeTime)
        {
            lifeTime -= deltaTime;
            if (lifeTime <= 0.0f)
            {
                destroyAction();
            }
        }
    }
}

void HActor::setLifeTime(const float lifeTime)
{
    this->lifeTime = lifeTime;
    isSetLifeTime = true;
}

void HActor::setIsSetLifeTime(const bool isSetLifeTime)
{
    this->isSetLifeTime = isSetLifeTime;
}

void HActor::registerFuncWhenActorLifeTimeZero(std::function<void()> func)
{
    destroyAction = func;
}

bool HActor::getIsSetLifeTime()
{
    return this->isSetLifeTime;
}

void HActor::setPendingKill(bool newPendingKill)
{
    isPendingKill = newPendingKill;
}

bool HActor::getPendingKill()
{
    return isPendingKill;
}