#pragma once

#include "AirplaneParent.h"

class ImageComponent;
class SpritesheetComponent;
class CollisionBoxComponent;
class AudioComponent;

enum class PLAYER_AIRPLANE_SHAPE
{
    SHAPE1,
    SHAPE2,
    SHAPE3
};

class Airplane :public AirplaneParent
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
    PLAYER_AIRPLANE_SHAPE getPlayerAirplaneShape();
    void setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE shape);
    void enableShield();
    void enableThunder();
    void playerInitWhenStageBegin();
    void playCoinSound();
    void setIsDie(bool isDie);
    bool getIsDie();
    void setFireRate(float rate);

private:
    void spawnPlayerBullet(std::pair<float, float>& spawnPos);

protected:
    void turnOnShield();
    void turnOffShield();

private:
    void shieldAnimation(float deltaTime);

private:
    AudioComponent* coinAudio = nullptr;
    AudioComponent* shieldAudio = nullptr;
    SpritesheetComponent* boosterSprite = nullptr;
    SpritesheetComponent* thunderAttack1 = nullptr;
    SpritesheetComponent* thunderAttack2 = nullptr;
    SpritesheetComponent* thunderAttack3 = nullptr;
    ImageComponent* shieldImage = nullptr;
    int attackPower = 25;
    int bulletCnt = 1;
    int missileCnt = 0;
    int shieldCnt = 0;
    int befTouchX = 0;
    int befTouchY = 0;
    PLAYER_AIRPLANE_SHAPE shape = PLAYER_AIRPLANE_SHAPE::SHAPE1;
    float shieldRotation = 0.0f;
    float accTimeForFlickering = 0.0f;
    float curShieldDuration = 5.0f;
    const float maxShieldDuration = 5.0f;
    bool canDestroyable = true;
    bool isThunderTime = false;
};