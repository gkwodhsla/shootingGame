//
// Created by lenovo on 2021-08-07.
//

#include "HActor.h"
#include "../Components/HSceneComponent.h"
#include <cmath>
#include <android/log.h>
#include <SDL.h>

HActor::HActor()
{
    rootComponent = new HSceneComponent();
}

HActor::~HActor()
{
    delete rootComponent;
    rootComponent = nullptr;
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


void HActor::setRootComponent(HSceneComponent *component)
{
    rootComponent = component;
}

std::pair<float, float> HActor::getActorDirectionalVector()
{
    return dirVec;
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

void HActor::update(float deltaTime)
{
    if(tickable)
    {
        rootComponent->update(deltaTime);

        if (isSetLifeTime)
        {
            lifeTime -= deltaTime;
            if (lifeTime <= 0.0f)
            {
                isPendingToKill = true;
            }
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

void HActor::setDestRotation(float dest)
{
    destRotation = dest;
}

void HActor::normalizeDirVec()
{
    float magnitude = sqrtf(dirVec.first*dirVec.first + dirVec.second*dirVec.second);

    if(magnitude!=0.0f)
    {
        dirVec.first /= magnitude;
        dirVec.second /= magnitude;
    }
}

bool HActor::getIsSetLifeTime()
{
    return this->isSetLifeTime;
}

