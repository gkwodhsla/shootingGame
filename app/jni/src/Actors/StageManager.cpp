#include "StageManager.h"
#include "../Framework.h"
#include "Spawner.h"
#include <android/log.h>

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

void StageManager::update(float deltaTime)
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
            //스테이지 클리어 후 처리할 코드를 여기에 삽입한다.
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "stage clear~~~");
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
    //최초 웨이브는 1 wave 부터임!
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