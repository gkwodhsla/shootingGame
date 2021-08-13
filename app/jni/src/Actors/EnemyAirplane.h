#pragma once
#include "Airplane.h"
#include "Bullet.h"

enum class ENEMY_SHIP_SHAPE
{
    SHIP1,
    SHIP2,
    SHIP3,
    SHIP4
};

class EnemyAirplane :public Airplane
{
public:
    EnemyAirplane() = delete;
    EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape);
    virtual ~EnemyAirplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;

//private:
    //void spawnBullet(); 추후 추가 예정

private:
    ImageComponent* hpBar;
    BULLET_COLOR bulletColor;
};

