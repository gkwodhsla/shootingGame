#pragma once

#include "AttackStrategy.h"

class StarStrategy: public AttackStrategy
{
public:
    StarStrategy();
    virtual ~StarStrategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;
private:
    Vector2D bossStarPattern[51];
    Vector2D bossStarPatternStartPos[51];
};