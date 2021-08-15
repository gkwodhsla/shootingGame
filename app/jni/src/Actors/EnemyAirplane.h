#pragma once
#include "Airplane.h"
#include "Bullet.h"

class SplineComponent;

enum class ENEMY_SHIP_SHAPE
{
    SHIP1,
    SHIP2,
    SHIP3,
    SHIP4,
    BOSS1,
    BOSS2
};

class EnemyAirplane :public Airplane
{
public:
    EnemyAirplane() = delete;
    EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape, int hp);
    virtual ~EnemyAirplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;
    void resetEnemyAirplaneToInitialState();

public:
    void getDamage(int damage);
    void setPath(SplineComponent* path);
//private:
    //void spawnBullet(); 추후 추가 예정

private:
    ImageComponent* hpBar = nullptr;
    SplineComponent* path = nullptr;
    BULLET_COLOR bulletColor;
    int curHp = 0;
    int maxHP = 0;
    float t = 0.0f;
    const int hpBarRowSize = 100;
    const int hpBarColSize = 10;
};

