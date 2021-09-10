#pragma once

#include "../../Level/MainLevel.h"
#include "../../Actors/Bullet.h"
#include "../../GlobalFunction.h"
#include "../../Vector2D.h"
#include "../../ActorObjectPool.h"
#include <cmath>

class AttackStrategy
{
public:
    AttackStrategy() = default;
    virtual ~AttackStrategy() = default;
    virtual void attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor) = 0;
    void spawnBulletFromPool(const std::pair<float, float>&spawnPos, float speed,
                             const Vector2D& dirVec, const BULLET_COLOR bulletColor)
    {
        MainLevel *mainLevel = GlobalFunction::Cast<MainLevel>(Framework::curLevel);
        ActorObjectPool<Bullet>* cont;
        cont = mainLevel->bulletPool;
        auto bullet = cont->acquireObject();
        bullet->init(spawnPos, bulletColor);
        bullet->setActorDirectionalVector(dirVec);
        bullet->changeBulletSpeed(speed);
    }
};