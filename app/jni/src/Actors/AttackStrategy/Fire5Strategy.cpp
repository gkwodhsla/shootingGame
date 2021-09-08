#include "Fire5Strategy.h"

Fire5Strategy::Fire5Strategy()
{
    Vector2D temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-30.0f);
    for (int i = 0; i < 5; ++i)
    {
        bulletDirVec[i] = temp;
        temp.rotateVector(15.0f);
    }
}

void Fire5Strategy::attackAction(const std::pair<float, float> &spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    for(int i = 0; i < 5; ++i)
    {
        AttackStrategy::spawnBulletFromPool(spawnPos, speed, bulletDirVec[i], bulletColor);
    }
}
