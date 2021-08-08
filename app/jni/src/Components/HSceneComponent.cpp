//
// Created by lenovo on 2021-08-07.
//

#include "HSceneComponent.h"
#include "../Framework.h"

HSceneComponent::HSceneComponent()
{
    componentTag = "HSceneComponent";
}

HSceneComponent::~HSceneComponent()
{

}

void HSceneComponent::render()
{
    for(auto&element:children)
    {
        element->render();
    }
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

void HSceneComponent::setComponentLocalLocation(const std::pair<int, int>& loc)
{
    localLocation = loc;
}

void HSceneComponent::setComponentLocalRotation(const float degree)
{
    localRotation = degree;
}

const std::pair<int, int> HSceneComponent::getComponentLocalLocation()
{
    return localLocation;
}

const float HSceneComponent::getComponentLocalRotation()
{
    return localRotation;
}

const HSceneComponent *HSceneComponent::getParentComponent()
{
    return parent;
}

void HSceneComponent::attachTo(HSceneComponent* component)
{
    this->parent = component;
    component->children.emplace_back(this);
}

