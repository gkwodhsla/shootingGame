//
// Created by lenovo on 2021-08-07.
//

#include "HSceneComponent.h"
#include "../Framework.h"
#include "../Actors/HActor.h"

HSceneComponent::HSceneComponent()
{
    componentTag = "HSceneComponent";
}

HSceneComponent::~HSceneComponent()
{

}

void HSceneComponent::updateComponentWorldRotation()
{
    if(parent)
    {
        worldRotation = parent->getComponentWorldRotation() + localRotation;
    }
    else if(!parent)
    {
        worldRotation = localRotation;
    }
    for(auto&element:children)
    {
        element->updateComponentWorldRotation();
    }
}

void HSceneComponent::updateComponentWorldLocation()
{
    if(parent)
    {
        auto parentLocalLocation = parent->getComponentWorldLocation();
        worldLocation = std::make_pair(parentLocalLocation.first + localLocation.first,
                                       parentLocalLocation.second + localLocation.second);
    }
    else if(!parent)
    {
        worldLocation = localLocation;
    }
    for(auto&element:children)
    {
        element->updateComponentWorldLocation();
    }
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
    for(auto& child:children)
    {
        child->update(deltaTime);
    }
}

const std::pair<float, float> HSceneComponent::getComponentWorldLocation()
{
    return worldLocation;
}

const float HSceneComponent::getComponentWorldRotation()
{
    return worldRotation;
}

void HSceneComponent::setComponentLocalLocation(const std::pair<float, float>& loc)
{
    localLocation = loc;
    updateComponentWorldLocation();
}

void HSceneComponent::setComponentLocalRotation(const float degree)
{
    localRotation = degree;
    updateComponentWorldRotation();
}

void HSceneComponent::setOwner(HActor *owner)
{
    this->owner = owner;
}

const std::pair<float, float> HSceneComponent::getComponentLocalLocation()
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
    component->children.push_back(this);

    auto parentLocalLocation = component->getComponentWorldLocation();
    worldLocation = std::make_pair(parentLocalLocation.first + localLocation.first,
                                   parentLocalLocation.second + localLocation.second);

    worldRotation = component->getComponentWorldRotation() + localRotation;
}

