#include "StageManager.h"
#include "../Framework.h"
#include "Spawner.h"
#include <android/log.h>
#include "../Level/MainLevel.h"
#include "../GlobalFunction.h"

using namespace GlobalFunction;

StageManager::StageManager()
{
    spawner = new Spawner();
}

StageManager::~StageManager()
{
    delete spawner;
    spawner = nullptr;
}

void StageManager::render()
{
    HActor::render();
}

void StageManager::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(isWaveBegin)
    {
        if(isEnemySpawning) //waveBegin으로 인해 isEnemySpawning이 true가 되면 스포너에게 적을 spawPerWave만큼 스폰하라고 알려준다.
        {
            spawner->startSpawn(spawnPerWave, enemyMaxHP, enemyFireRate);
            curEnemyAirplaneNum = spawnPerWave;
            isEnemySpawning = false;
        }
        else if(isBossTime && !isBossKilled)
        {
            spawner->spawnBoss(0, bossMaxHP, bossFireRate);
            isBossTime = false;
        }
        if(!isNormalWaveEnd && curEnemyAirplaneNum<=0)
        {
            ++curWave;
            if(curWave > maxWave)//현재 wave가 맥스 웨이브를 넘기면 보스 웨이브로 넘어간다.
            {
                bossWaveBegin();
            }
            else
            {
                isEnemySpawning = true;
            }
        }
        if(isBossKilled)
        {
            MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
            mainLevel->stageClear();
            stageClear();
        }
    }
    spawner->update(deltaTime);
}

void StageManager::waveBegin()
{
    isEnemySpawning = true;
    isWaveBegin = true;
    curWave = 1;
    isNormalWaveEnd = false;
    //최초 웨이브는 1 wave 부터임
}

void StageManager::bossWaveBegin()
{
    isBossTime = true;
    isBossKilled = false;
    isNormalWaveEnd = true;
}

void StageManager::enemyAirplaneDie()
{
    --curEnemyAirplaneNum;
}

void StageManager::bossDie()
{
    isBossKilled = true;
}

void StageManager::stageClear()
{
    isEnemySpawning = false;
    isWaveBegin = false;
    isBossTime = false;
    isBossKilled = false;
    isNormalWaveEnd = false;
    spawner->stopSpawn();
}

void StageManager::setStage(int stage)
{
    curStage = stage;
    spawnPerWave = 2 + 2 * (stage / 10); //10스테이지 마다 웨이브에 2마리의 적이 추가된다.
    if(spawnPerWave >= 12)
    {
        spawnPerWave = 12;
    }
    maxWave = 2 + stage / 10; //웨이브는 10스테이지마다 1씩 추가된다.
    if(maxWave >= 6)
    {
        maxWave = 6;
    }
    enemyMaxHP = 50 + 20 * (stage / 5);
    bossMaxHP = 300 + stage * 50;
    enemyFireRate = 3.0f - 0.02f * stage;
    if(enemyFireRate <= 0.5f)
        enemyFireRate = 0.5f;

    bossFireRate = 3.0f - 0.03f * stage;
    if(bossFireRate <= 1.0f)
        bossFireRate = 1.0f;
}
