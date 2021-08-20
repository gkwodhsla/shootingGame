#pragma once
#include "HActor.h"

class Spawner;
class StageManager :public HActor
{
public:
    StageManager();
    virtual ~StageManager();
    virtual void render();
    virtual void update(float deltaTime);
    void waveBegin(); // 스테이지가 시작된다면 1웨이브 부터 시작한다!
    void bossWaveBegin();
    void enemyAirplaneDie();
    void bossDie();

private:
    int curStage = 0;
    int curWave = 1;
    int maxWave = 2;
    int spawnPerWave = 2;
    int maxHP = 100;
    int bossMaxHP = 300;
    int maxFireRate = 1.0f;
    int bossFireRate = 1.0f;
    int canUsingPatternNumber = 1;
    int curEnemyAirplaneNum = 0;
    float enemyBulletSpeed = 700.0f;
    float bossEnemyBulletSpeed = 500.0f;
    bool isEnemySpawning = false;
    bool isWaveBegin = false;
    bool isBossTime = false;
    bool isBossKilled = false;
    Spawner* spawner = nullptr;
};