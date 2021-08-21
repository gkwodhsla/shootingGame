#pragma once

#include "HLevelBase.h"
#include "../Actors/Bullet.h"
#include <random>

class Airplane;
class EnemyAirplane;
class Bullet;
class StageManager;
class Canvas;

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
    void checkingCollision();
    friend class Airplane;
    friend class Spawner;
    friend class EnemyAirplane;
    friend class StageManager;

private:
    void addBulletToBuffer(std::vector<Bullet*>& cont, BULLET_COLOR color);
    void stageClear();

private:
    StageManager* stageManager = nullptr;
    Airplane* playerAirplane = nullptr;
    std::vector<Bullet*> playerBullets;
    std::vector<Bullet*> enemyRedBullets;
    std::vector<Bullet*> enemyPurpleBullets;
    std::vector<Bullet*> enemyBlueBullets;
    std::vector<Bullet*> enemySkyBullets;
    std::vector<EnemyAirplane*> enemyAirplanes;
    EnemyAirplane* boss1 = nullptr;
    EnemyAirplane* boss2 = nullptr;
    const int playerBulletSize = 100;
    const int enemyBulletSize = 100;
    float coolTime = 3.0f;
    Canvas* shopCanvas = nullptr;
};

extern std::random_device rd;
extern std::default_random_engine dre;