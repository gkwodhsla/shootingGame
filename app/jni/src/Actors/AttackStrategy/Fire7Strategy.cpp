#include "Fire7Strategy.h"

Fire7Strategy::Fire7Strategy()
{
    Vector2D temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-45.0f);
    for (int i = 0; i < 7; ++i)
    {
        bulletDirVec[i] = temp;
        temp.rotateVector(15.0f);
    }
}

void Fire7Strategy::attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    for(int i = 0; i < 7; ++i)
    {
        AttackStrategy::spawnBulletFromPool(spawnPos, speed, bulletDirVec[i], bulletColor);
    }
}
