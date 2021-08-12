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
    HSceneComponent* ownerRootComp = owner->getRootComponent();
    auto befPos = ownerRootComp->getComponentLocalLocation();

    std::pair<float, float> newPos;

    newPos.first = befPos.first + (initVelocity.first * deltaTime)+
            (0.5f * acceleration.first * deltaTime * deltaTime);

    newPos.second = befPos.second + (initVelocity.second * deltaTime)+
                    (0.5f * acceleration.second * deltaTime * deltaTime);

    ownerRootComp->setComponentLocalLocation(newPos);
    //거리 = 이전 거리 + 초기 속도 * 시간 + (0.5 * 가속도 * 시간^2)
    //여기에다가 방향벡터를 갱신하는 수식을 작성한다.
    //현재 위치 - 이전 위치 하고 정규화

}
