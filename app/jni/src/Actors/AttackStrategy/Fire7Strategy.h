#pragma once

#include "AttackStrategy.h"

class Fire7Strategy final : public AttackStrategy
{
public:
    Fire7Strategy();
    virtual ~Fire7Strategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;

private:
    Vector2D bulletDirVec[7];
};