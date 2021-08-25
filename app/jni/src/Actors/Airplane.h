#pragma once

#include "HPawn.h"

class ImageComponent;
class SpritesheetComponent;
class CollisionBoxComponent;

enum class PLAYER_AIRPLANE_SHAPE
{
    SHAPE1,
    SHAPE2,
    SHAPE3
};

class Airplane :public HPawn
{
public:
    Airplane();
    virtual ~Airplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;

public:
    CollisionBoxComponent* getCollisionBoxComp();
    int getPlayerAttackPower();
    void setPlayerAttackPower(int attackPower);
    int getPlayerBulletCnt();
    void setPlayerBulletCnt(int bulletCnt);
    int getMissileCnt();
    void setMissileCnt(int missileCnt);
    int getShieldCnt();
    void setShieldCnt(int shieldCnt);
    void setFireRate(float rate);
    PLAYER_AIRPLANE_SHAPE getPlayerAirplaneShape();
    void setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE shape);

private:
    void spawnPlayerBullet(std::pair<float, float>& spawnPos);

protected:
    ImageComponent* airplaneImg = nullptr;
    SpritesheetComponent* explosionSprite = nullptr;
    CollisionBoxComponent* collisionBox = nullptr;
    float fireRate = 1.0f;
    float curFireTime = 0.5f;

protected:
    void turnOffBooster();
    void turnOnShield();
    void turnOffShield();

private:
    SpritesheetComponent* boosterSprite = nullptr;
    ImageComponent* shieldImage = nullptr;
    int attackPower = 50;
    int bulletCnt = 1;
    int missileCnt = 0;
    int shieldCnt = 0;
    PLAYER_AIRPLANE_SHAPE shape = PLAYER_AIRPLANE_SHAPE::SHAPE1;
    float shieldRotation = 0.0f;
    float accTimeForFlickering = 0.0f;
};