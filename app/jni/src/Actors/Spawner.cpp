#include "Spawner.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/EnemyAirplane.h"
#include <android/log.h>
#include "../GlobalFunction.h"
#include <initializer_list>

using namespace GlobalFunction;

const int Spawner::numOfDestX = 4;
const int Spawner::numOfDestY = 3;

std::uniform_int_distribution<int> uid(0,Spawner::numOfDestY * Spawner::numOfDestX - 1);
std::uniform_int_distribution<int> enemyPattern(0, 3);
std::uniform_int_distribution<int> bossPattern(0, 2);

Spawner::Spawner()
{
    int totalDest = numOfDestY * numOfDestX;
    pathMiddle.reserve(totalDest);

    for(int i = 0; i < numOfDestY; ++i)
    {
        for(int j = 0; j < numOfDestX; ++j)
        {
            std::initializer_list<std::pair<int, int>> middleData = {{Framework::RTWidth/2, -100},
                                                                     {Framework::RTWidth/2, 500},
                                                                     {destX[j], destY[i]}};
            pathMiddle.emplace_back(middleData, 0.0f, this);
        }
    }

    bossPath = createComponent<SplineComponent>(std::initializer_list<std::pair<int, int>>{std::make_pair(Framework::RTWidth/2 - 250.0f, -1000),
                                    std::make_pair(Framework::RTWidth/2 - 250.0f, 100)}, 1.0f, this);
}

Spawner::~Spawner()
{

}

void Spawner::render()
{
    HActor::render();

    /*for(int i=0;i<pathLeft.size();++i)
    {
        pathLeft[i].drawDebugLine();
    }*/
}

void Spawner::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(isSpawning)
    {
        spawnCoolTime -= deltaTime;
        if(spawnCoolTime <= 0.0f)
        {
            MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
            auto enemies = mainLevel->enemyAirplanes;
            for(int i = 0; i < enemies.size(); ++i)
            {
                if(!enemies[i]->getVisibility())
                {
                    int spawnIndex = 0;
                    while(1)
                    {
                        spawnIndex = uid(dre);
                        if(pathMiddle[spawnIndex].getUsable())
                        {
                            pathMiddle[spawnIndex].setUsable(false);
                            break;
                        }
                    }
                    enemies[i]->setVisibility(true);
                    enemies[i]->setActorTickable(true);
                    enemies[i]->setPath(&pathMiddle[spawnIndex]);
                    enemies[i]->setCanDamaged(true);
                    enemies[i]->setMaxHP(maxHP);
                    enemies[i]->setFireRate(fireRate);
                    enemies[i]->setIsDie(false);

                    int enemyPatternNum = enemyPattern(dre);
                    if(enemyPatternNum == 0)
                    {
                        enemies[i]->setBulletPattern(ENEMY_BULLET_PATTERN::BULLET_3);
                    }
                    else if(enemyPatternNum == 1)
                    {
                        enemies[i]->setBulletPattern(ENEMY_BULLET_PATTERN::BULLET_5);
                    }
                    else if(enemyPatternNum == 2)
                    {
                        enemies[i]->setBulletPattern(ENEMY_BULLET_PATTERN::BULLET_7);
                    }
                    else
                    {
                        enemies[i]->setBulletPattern(ENEMY_BULLET_PATTERN::TARGETED);
                    }
                    --maxSpawnedCnt;
                    break;
                }
            }
            spawnCoolTime = maxSpawnCoolTime;
            if(maxSpawnedCnt == 0)
            {
                isSpawning = false;
            }
        }
    }
    else if(isBossTime) // 보스가 등장할 때!
    {
        EnemyAirplane* curBoss = nullptr;
        if(bossIndex == 0)
        {
            auto *mainLevel = Cast<MainLevel>(Framework::curLevel);
            curBoss = mainLevel->boss1;
        }
        else
        {
            auto *mainLevel = Cast<MainLevel>(Framework::curLevel);
            curBoss = mainLevel->boss2;
        }
        curBoss->setVisibility(true);
        curBoss->setActorTickable(true);
        curBoss->setPath(bossPath);
        curBoss->setCanDamaged(true);
        curBoss->setMaxHP(bossMaxHP);
        curBoss->setFireRate(bossFireRate);

        int bossPatternNum = bossPattern(dre);
        if(bossPatternNum == 0)
        {
            curBoss->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_CIRCLE);
        }
        else if(bossPatternNum == 1)
        {
            curBoss->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_STAR);
        }
        else
        {
            curBoss->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_FLOWER);
        }
        isBossTime = false;

    }
}

void Spawner::startSpawn(int enemyCnt, int maxHP, float fireRate)
{
    isSpawning = true;
    spawnCoolTime = 2.0f;
    maxSpawnedCnt = enemyCnt;
    this->maxHP = maxHP;
    this->fireRate = fireRate;
}

void Spawner::stopSpawn()
{
    isSpawning = false;
    spawnCoolTime = maxSpawnCoolTime;
    maxSpawnedCnt = 0;
}

void Spawner::spawnBoss(int whichBoss, int maxHP, float fireRate)
{
    isBossTime = true;
    isSpawning = false;
    bossIndex = whichBoss;
    bossMaxHP = maxHP;
    bossFireRate = fireRate;
}

int Spawner::getPathNum()
{
    return numOfDestX * numOfDestY;
}