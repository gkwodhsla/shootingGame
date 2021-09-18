#pragma once

#include "AttackStrategy.h"

class Fire5Strategy final : public AttackStrategy
{
public:
    Fire5Strategy();
    virtual ~Fire5Strategy() = default;
    void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) override;

private:
    Vector2D bulletDirVec[5];
};