#pragma once
#include "HActor.h"

class Spawner;
class StageManager :public HActor
{
public:
    StageManager();
    StageManager(const StageManager&) = delete;
    StageManager& operator=(const StageManager&) = delete;
    virtual ~StageManager();
    virtual void render();
    virtual void update(const float deltaTime);
    void waveBegin(); // 스테이지가 시작된다면 1웨이브 부터 시작한다!
    void bossWaveBegin();
    void enemyAirplaneDie();
    void bossDie();
    void stageClear();
    void setStage(int stage);

private:
    int curStage = 0;
    int curWave = 1;
    int maxWave = 2;
    int spawnPerWave = 2;
    int enemyMaxHP = 50;
    int bossMaxHP = 300;
    float enemyFireRate = 3.0f;
    float bossFireRate = 2.5f;
    int curEnemyAirplaneNum = 0;
    float enemyBulletSpeed = 700.0f;
    float bossEnemyBulletSpeed = 500.0f;
    bool isEnemySpawning = false;
    bool isWaveBegin = false;
    bool isBossTime = false;
    bool isBossKilled = false;
    bool isNormalWaveEnd = false;
    Spawner* spawner = nullptr;
};