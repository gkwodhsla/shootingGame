#pragma once

#include "HComponent.h"
#include <utility>

class HActor;

class MovementComponent :public HComponent
{
public:
    MovementComponent() = delete;
    MovementComponent(const MovementComponent&) = delete;
    MovementComponent& operator=(const MovementComponent&) = delete;
    MovementComponent(HActor* owner);
    virtual ~MovementComponent() = default;
    virtual void update(const float deltaTime);
    void setSpeed(float speed);
    void setAcceleration(const std::pair<float, float>& accel);

private:
    void updatePosition(const float deltaTime);

private:
    std::pair<float, float> acceleration;
    float speed = 0.0f;
};


