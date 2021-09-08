#include "StarStrategy.h"

StarStrategy::StarStrategy()
{
    float t = 0.0f;
    int index = 0;
    Vector2D befDir{ -9 * sin(2 * t) - 5 * sin(3 * t), 9 * cos(2 * t) - 5 * cos(3 * t) };
    bossStarPatternStartPos[index] = befDir;

    Vector2D curDir{ 0.0f, 0.0f };

    for (t = 0.1256f; t <= 3.14f * 2.0f; t += 0.1256f)
    {
        float curX = -9 * sin(2 * t) - 5 * sin(3 * t);
        float curY = 9 * cos(2 * t) - 5 * cos(3 * t);
        curDir = Vector2D{ curX, curY };

        Vector2D v1 = curDir - befDir;

        if (abs(v1.x) >= 3.5f)
            v1.x = 1.5f;
        bossStarPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossStarPatternStartPos[index] = Vector2D{ curX * 10.0f, curY * 10.0f };
    }
}

void StarStrategy::attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    int bulletCnt = 49;
    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool({bossStarPatternStartPos[i].x + spawnPos.first,bossStarPatternStartPos[i].y + spawnPos.second },
                            500.0f, bossStarPattern[i], bulletColor);
        bossStarPattern[i].rotateVector(5.0f);
    }
}
