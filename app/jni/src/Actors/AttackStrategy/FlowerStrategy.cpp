#include "FlowerStrategy.h"

FlowerStrategy::FlowerStrategy()
{
    float t = 0.0f;
    int index = 0;
    Vector2D befDir{ 20 * cos(3 * t) * cos(t), 20 * cos(3 * t) * sin(t) };
    bossFlowerPatternStartPos[index] = befDir;

    Vector2D curDir{ 0.0f, 0.0f };

    for (t = 0.08f; t <= 3.2f; t += 0.08f)
    {
        float curX = 20 * cos(3 * t) * cos(t);
        float curY = 20 * cos(3 * t) * sin(t);
        curDir = Vector2D{ curX, curY };

        Vector2D v1 = curDir - befDir;
        v1.normalize();

        bossFlowerPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossFlowerPatternStartPos[index] = Vector2D{ curX * 10.0f, curY * 10.0f };
    }
}

void FlowerStrategy::attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    int bulletCnt = 40;
    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool({bossFlowerPatternStartPos[i].x + spawnPos.first,
                             bossFlowerPatternStartPos[i].y + spawnPos.second}, 900.0f,
                            bossFlowerPattern[i], bulletColor);
        bossFlowerPattern[i].rotateVector(5.0f);
    }
}
