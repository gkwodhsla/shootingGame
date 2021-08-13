#pragma once

#include "HPawn.h"

class ImageComponent;
class SpritesheetComponent;
class CollisionBoxComponent;

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

private:
    void spawnPlayerBullet(const std::pair<float, float>& spawnPos);

protected:
    ImageComponent* airplaneImg = nullptr;
    SpritesheetComponent* explosionSprite = nullptr;
    CollisionBoxComponent* collisionBox = nullptr;
    float fireRate = 0.5f;
    float curFireTime = 0.5f;

protected:
    void turnOffBooster();

private:
    SpritesheetComponent* boosterSprite = nullptr;
    int attackPower = 10;
};