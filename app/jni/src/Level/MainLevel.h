#pragma once

#include "HLevelBase.h"
#include "../Actors/Bullet.h"
#include <random>

class Airplane;
class EnemyAirplane;
class Bullet;
class StageManager;
class Canvas;
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
    friend class Airplane;
    friend class Spawner;
    friend class EnemyAirplane;
    friend class StageManager;

private:
    void stageClear();

public:
    ActorObjectPool<Bullet>* bulletPool;

private:
    StageManager* stageManager = nullptr;
    Airplane* playerAirplane = nullptr;
    std::vector<EnemyAirplane*> enemyAirplanes;
    EnemyAirplane* boss1 = nullptr;
    EnemyAirplane* boss2 = nullptr;
    const int playerBulletSize = 100;
    const int enemyBulletSize = 100;
    float coolTime = 3.0f;
    Canvas* shopCanvas = nullptr;
    Canvas* inGameCanvas = nullptr;
};

extern std::random_device rd;
extern std::default_random_engine dre;