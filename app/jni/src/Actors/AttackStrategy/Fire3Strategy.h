#pragma once

#include "AttackStrategy.h"

class Fire3Strategy: public AttackStrategy
{
public:
    Fire3Strategy();
    virtual ~Fire3Strategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;

private:
    Vector2D bulletDirVec[3];
};