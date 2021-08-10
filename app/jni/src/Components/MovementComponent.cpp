#include "MovementComponent.h"
#include "../Actors/HActor.h"

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
    //이동하는 코드 작성
}
