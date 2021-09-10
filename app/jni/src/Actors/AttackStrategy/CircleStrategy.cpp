#include "CircleStrategy.h"

CircleStrategy::CircleStrategy()
{
    float toRad = 3.14f / 180.0f;
    float t = 0.0f;

    Vector2D befDir{ 1.0f, 0.0f };
    Vector2D curDir{ 0.0f, 0.0f };
    int index = 0;
    for (t = 0.0333f; t <= 1.0f; t += 0.0333f)
    {
        float curX = cos(t * 360.0f * toRad);
        float curY = sin(t * 360.0f * toRad);
        curDir = Vector2D{ curX, curY };

        Vector2D v1 = curDir - befDir;
        v1.normalize();
        bossCirclePattern[index++] = Vector2D(v1.y, -v1.x);
        //Up vector를 (0, 0, -1.0f)라고 가정하고 v1과 외적한 결과이다.

        befDir = curDir;

    }
}

void CircleStrategy::attackAction(const std::pair<float, float> &spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    int bulletCnt = 30;

    float randomRotation = randomRot(dre);
    for(int i = 0; i < bulletCnt; ++i)
    {
        AttackStrategy::spawnBulletFromPool(spawnPos, speed, bossCirclePattern[i], bulletColor);
        bossCirclePattern[i].rotateVector(randomRotation);
    }
}
