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
    for(auto& child:children)
    {
        child->updateComponentWorldRotation();
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
    else if(!parent) //부모가 없다면 rootComponent이다. rootComponent는 월드와 로컬이 같다.
    {
        worldLocation = localLocation;
    }
    for(auto& child:children)
    {
        child->updateComponentWorldLocation();
    }
}

void HSceneComponent::render()
{
    for(auto& child:children)
    {
        child->render();
    }
}

void HSceneComponent::update(float deltaTime)
{
    for(auto& child:children)
    {
        child->update(deltaTime);
    }
}

std::pair<float, float> HSceneComponent::getComponentWorldLocation()
{
    return worldLocation;
}

float HSceneComponent::getComponentWorldRotation()
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

std::pair<float, float> HSceneComponent::getComponentLocalLocation()
{
    return localLocation;
}

float HSceneComponent::getComponentLocalRotation()
{
    return localRotation;
}

HSceneComponent *HSceneComponent::getParentComponent()
{
    return parent;
}

void HSceneComponent::attachTo(HSceneComponent* component)
{
    this->parent = component;
    component->children.push_back(this);

    auto parentWorldLocation = component->getComponentWorldLocation();
    worldLocation = std::make_pair(parentWorldLocation.first + localLocation.first,
                                   parentWorldLocation.second + localLocation.second);

    worldRotation = component->getComponentWorldRotation() + localRotation;
}

