#pragma once

#include "AttackStrategy.h"

class FlowerStrategy final: public AttackStrategy
{
public:
    FlowerStrategy();
    virtual ~FlowerStrategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;

private:
    Vector2D bossFlowerPattern[41];
    Vector2D bossFlowerPatternStartPos[41];
};