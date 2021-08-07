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

const std::pair<int, int> HSceneComponent::getComponentWorldLocation()
{
    return std::make_pair(-99999, -99999);
}

const float HSceneComponent::getComponentWorldRotation()
{
    return 0;
}

const std::pair<int, int> HSceneComponent::getComponentLocalLocation()
{
    return std::make_pair(-99999, -99999);
}

const float HSceneComponent::getComponentLocalRotation()
{
    return 0;
}

const HSceneComponent *HSceneComponent::getParentComponent()
{
    return NULL;
}

void HSceneComponent::attachTo()
{

}
