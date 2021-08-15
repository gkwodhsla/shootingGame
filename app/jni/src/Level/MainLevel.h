#pragma once

#include "HLevelBase.h"

class Airplane;
class EnemyAirplane;
class Bullet;
class SplineComponent;

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
private:
    Airplane* playerAirplane = nullptr;
    EnemyAirplane* enemyTemp = nullptr;
    std::vector<Bullet*> playerBullets;
    std::vector<EnemyAirplane*> enemyAirplanes;
    const int playerBulletSize = 100;
    const int enemySize = 30;
    SplineComponent* tempSpline = nullptr;
};