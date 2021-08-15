#pragma once
#include "HActor.h"
#include "../Components/SplineComponent.h"

class Spawner :public HActor
{
public:
    Spawner();
    virtual ~Spawner();
    void render() override;
    void update(float deltaTime) override;
    void startSpawn(int enemyCnt); //레벨에서 특정 시점마다 이 함수를 호출해 적 비행기를 스폰하게 해준다.

public:
    int getPathNum();

public:
    static const int numOfDestX;
    static const int numOfDestY;
private:
    std::vector<SplineComponent> pathMiddle;
    std::vector<SplineComponent> pathLeft;
    std::vector<SplineComponent> pathRight;
    float spawnCoolTime = 0.0f;
    float maxSpawnCoolTime = 0.5f;
    int destX[4] = {100, 350, 600, 850};
    int destY[5] = {30, 250, 500, 750, 1000};
    bool isSpawning = false;
    int maxSpawnedCnt = 0;
};