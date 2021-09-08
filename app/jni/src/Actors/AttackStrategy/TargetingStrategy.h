#pragma once
#include "AttackStrategy.h"

class TargetingStrategy: public AttackStrategy
{
public:
    TargetingStrategy() = default;
    virtual ~TargetingStrategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;
};