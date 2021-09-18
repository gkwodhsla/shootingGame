#pragma once

#include "AttackStrategy.h"

class CircleStrategy final : public AttackStrategy
{
public:
    CircleStrategy();
    virtual ~CircleStrategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;

private:
    Vector2D bossCirclePattern[31];
};