#pragma once

#include "HLevelBase.h"
#include "../Actors/Bullet.h"
#include <random>

class Airplane;
class EnemyAirplane;
class Bullet;
class StageManager;
class Canvas;
class Crystal;
class BackgroundActor;
template<typename T>
class ActorObjectPool;

class MainLevel: public HLevelBase
{
public:
    MainLevel();
    virtual ~MainLevel();
    void handleEvent(SDL_Event& e) override;
    void update(float deltaTime) override;
    void render() override;
    void enter() override;
    void exit() override;
    void killAllEnemyAirplane();
    void stageClear();
    friend class Airplane;
    friend class Spawner;
    friend class EnemyAirplane;
    friend class StageManager;

private:
    void afterStageClear();
    void writeGameDataToDB();
    void initDataUsingDataReadFromDB();
public:
    ActorObjectPool<Bullet>* bulletPool;
    ActorObjectPool<Crystal>* crystalPool;

private:
    BackgroundActor* bgActor = nullptr;
    StageManager* stageManager = nullptr;
    Airplane* playerAirplane = nullptr;
    std::vector<EnemyAirplane*> enemyAirplanes;
    EnemyAirplane* boss1 = nullptr;
    EnemyAirplane* boss2 = nullptr;
    const int playerBulletSize = 100;
    const int enemyBulletSize = 100;
    float coolTime = 3.0f;
    const float maxCoolTime = 3.0f;
    bool isClear = false;
};

extern std::random_device rd;
extern std::default_random_engine dre;