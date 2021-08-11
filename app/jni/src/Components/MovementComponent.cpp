#include "MovementComponent.h"
#include "../Actors/HActor.h"
#include "HSceneComponent.h"

MovementComponent::MovementComponent(HActor* owner)
{
    this->owner = owner;
    componentTag = "MovementComponent";
}

void MovementComponent::update(float deltaTime)
{
    updatePosition(deltaTime);
}

void MovementComponent::setInitialVelocity(const std::pair<float, float> &vel)
{
    initVelocity = vel;
}

void MovementComponent::setAcceleration(const std::pair<float, float> &accel)
{
    acceleration = accel;
}

void MovementComponent::updatePosition(const float deltaTime)
{
    //const HSceneComponent* ownerRootComp = owner->getRootComponent();
    //auto befPos = ownerRootComp->getComponentLocalLocation();
    //auto actorDirVec = owner->getActorDirectionalVector();

    //거리 = 이전 거리 + 초기 속도 * 시간 + (0.5 * 가속도 * 시간^2)

}
