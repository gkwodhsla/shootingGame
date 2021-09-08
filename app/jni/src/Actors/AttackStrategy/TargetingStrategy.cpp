#include "TargetingStrategy.h"
#include "../HPawn.h"

void TargetingStrategy::attackAction(const std::pair<float, float>&spawnPos, const float speed, const BULLET_COLOR bulletColor)
{
    auto playerPos = GlobalFunction::GetPlayerPawn()->getActorWorldLocation();
    auto newX = (float)playerPos.first - spawnPos.first;
    auto newY = (float)playerPos.second - spawnPos.second;
    Vector2D dirVec{newX, newY};
    dirVec.normalize();
    AttackStrategy::spawnBulletFromPool(spawnPos, speed, dirVec, bulletColor);
}