#pragma once

#include "HLevelBase.h"

class Airplane;
class EnemyAirplane;
class Bullet;
class Spawner;

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
private:
    Airplane* playerAirplane = nullptr;
    Spawner* spawner = nullptr;
    std::vector<Bullet*> playerBullets;
    std::vector<EnemyAirplane*> enemyAirplanes;
    const int playerBulletSize = 100;
    float coolTime = 3.0f;
};