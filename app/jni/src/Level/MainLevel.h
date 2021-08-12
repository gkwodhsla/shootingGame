#pragma once

#include "HLevelBase.h"

class Airplane;
class Bullet;

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

private:
    Airplane* playerAirplane = nullptr;
    std::vector<Bullet*> playerBullets;
};