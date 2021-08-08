//
// Created by lenovo on 2021-08-07.
//

#include "HActor.h"
#include "../Components/HSceneComponent.h"

HActor::HActor()
{

}

HActor::~HActor()
{

}

void HActor::moveTo(const std::pair<int, int> &loc)
{

}

void HActor::rotateActor(float degree)
{

}

void HActor::setVisibility(bool isVisible)
{

}

const bool HActor::getVisibility()
{
    return 0;
}

void HActor::setRootComponent(HSceneComponent *component)
{

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

}

const bool HActor::getActorTickable()
{
    return 0;
}

void HActor::render()
{
    rootComponent->render();
}

void HActor::update()
{

}
