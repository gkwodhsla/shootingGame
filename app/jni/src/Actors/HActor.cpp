//
// Created by lenovo on 2021-08-07.
//

#include "HActor.h"
#include "../Components/HSceneComponent.h"

void HActor::moveTo(const std::pair<int, int> &loc)
{
    rootComponent->setComponentLocalLocation(loc);
}

void HActor::rotateActor(float degree)
{
    rootComponent->setComponentLocalRotation(degree);
}

void HActor::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

const bool HActor::getVisibility()
{
    return visibility;
}

void HActor::setRootComponent(HSceneComponent *component)
{
    rootComponent = component;
}

const std::pair<int, int> HActor::getActorDirectionalVector()
{
    return dirVec;
}

const std::pair<int, int> HActor::getActorWorldLocation()
{
    return rootComponent->getComponentLocalLocation();
}

const float HActor::getActorWorldRotation()
{
    return rootComponent->getComponentLocalRotation();
}

void HActor::setActorTickable(bool isTickable)
{
    tickable = isTickable;
}

const bool HActor::getActorTickable()
{
    return tickable;
}

void HActor::render()
{
    rootComponent->render();
}

void HActor::update(float deltaTime)
{
    if(isSetLifeTime)
    {
        lifeTime -= deltaTime;
        if(lifeTime <= 0.0f)
        {
            isPendingToKill = true;
        }
    }
}

void HActor::setLifeTime(const float lifeTime)
{
    this->lifeTime = lifeTime;
}
void HActor::setIsSetLifeTime(const bool isSetLifeTime)
{
    this->isSetLifeTime = isSetLifeTime;
}
const bool HActor::getIsSetLifeTime()
{
    return this->isSetLifeTime;
}