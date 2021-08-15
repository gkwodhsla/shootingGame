#include "Spawner.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/EnemyAirplane.h"
//{-100, 1200},
//                                      {900, 1000},
//                                      {Framework::rendererWidth/2,700},
//왼쪽 path

//{Framework::rendererWidth + 100, 1200},
//{Framework::rendererWidth - 900, 1000},
//{Framework::rendererWidth/2,700}
//오른쪽 path

//{Framework::rendererWidth/2, -100},
//{Framework::rendererWidth/2, 500}
//가운데 path

const int Spawner::numOfDestX = 4;
const int Spawner::numOfDestY = 5;

Spawner::Spawner()
{
    int totalDest = numOfDestY * numOfDestX;
    pathLeft.reserve(totalDest);
    pathMiddle.reserve(totalDest);
    pathRight.reserve(totalDest);

    for(int i = 0; i < numOfDestY; ++i)
    {
        for(int j = 0; j < numOfDestX; ++j)
        {
            std::initializer_list<std::pair<int, int>> leftData = {{-100, 1200},
                                                              {900, 1000},
                                                              {Framework::rendererWidth/2,700},
                                                              {destX[j], destY[i]}};
            pathLeft.emplace_back(leftData, 0.0f, this);

            std::initializer_list<std::pair<int, int>> middleData = {{Framework::rendererWidth/2, -100},
                                                                     {Framework::rendererWidth/2, 500},
                                                                     {destX[j], destY[i]}};
            pathMiddle.emplace_back(middleData, 0.0f, this);

            std::initializer_list<std::pair<int, int>> rightData = {{Framework::rendererWidth + 100, 1200},
                                                                    {Framework::rendererWidth - 900, 1000},
                                                                    {Framework::rendererWidth/2,700},
                                                                    {destX[j], destY[i]}};
            pathRight.emplace_back(rightData, 0.0f, this);
        }
    }
}

Spawner::~Spawner()
{

}

void Spawner::render()
{
    HActor::render();
}

void Spawner::update(float deltaTime)
{
    HActor::update(deltaTime);
    if(isSpawning)
    {
        spawnCoolTime -= deltaTime;
        if(spawnCoolTime <= 0.0f)
        {
            --maxSpawnedCnt;

            MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
            auto enemies = mainLevel->enemyAirplanes;
            for(int i = 0; i < enemies.size(); ++i)
            {
                if(!enemies[i]->getVisibility())
                {
                    enemies[i]->setVisibility(true);
                    enemies[i]->setActorTickable(true);
                    enemies[i]->setPath(&pathLeft[4]);
                    break;
                }
            }
            //레벨에서 에너미 버퍼를 가져와서 활성화 시킨다.
            spawnCoolTime = maxSpawnCoolTime;
            if(maxSpawnedCnt == 0)
            {
                isSpawning = false;
            }
        }
    }
}

void Spawner::startSpawn(int enemyCnt)
{
    isSpawning = true;
    spawnCoolTime = 0.0f;
    maxSpawnedCnt = enemyCnt;
}

int Spawner::getPathNum()
{
    return numOfDestX * numOfDestY;
}