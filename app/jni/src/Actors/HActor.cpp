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

}
