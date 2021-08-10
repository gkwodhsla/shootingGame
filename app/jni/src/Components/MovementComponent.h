#pragma once

#include "HComponent.h"
#include <utility>

class HActor;

class MovementComponent :public HComponent
{
public:
    MovementComponent() = delete;
    MovementComponent(HActor* owner);
    virtual ~MovementComponent() = default;
    virtual void update(float deltaTime);
    void setInitialVelocity(const std::pair<float, float>& vel);
    void setAcceleration(const std::pair<float, float>& accel);
    void updatePosition(const float deltaTime);
private:
    std::pair<float, float> initVelocity;
    std::pair<float, float> acceleration;
};


