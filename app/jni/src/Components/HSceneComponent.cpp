//
// Created by lenovo on 2021-08-07.
//

#include "HSceneComponent.h"

HSceneComponent::HSceneComponent() {

}

HSceneComponent::~HSceneComponent() {

}

void HSceneComponent::componentRotation(float degree) {

}

void HSceneComponent::componentMoveTo(std::pair<int, int> &location) {

}

void HSceneComponent::update(float deltaTime)
{

}

std::pair<int, int> HSceneComponent::getComponentWorldLocation()
{
    return std::make_pair(-99999, -99999);
}

float HSceneComponent::getComponentWorldRotation()
{
    return 0;
}

std::pair<int, int> HSceneComponent::getComponentLocalLocation()
{
    return std::make_pair(-99999, -99999);
}

float HSceneComponent::getComponentLocalRotation()
{
    return 0;
}

HSceneComponent *HSceneComponent::getParentComponent()
{
    return NULL;
}

void HSceneComponent::attachTo()
{

}
