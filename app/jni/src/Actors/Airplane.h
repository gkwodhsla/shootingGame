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
    Airplane(const Airplane&) = delete;
    Airplane& operator=(const Airplane&) = delete;
    virtual ~Airplane();
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    virtual void handleEvent(const SDL_Event& e) override;

public:
    CollisionBoxComponent* getCollisionBoxComp();
    int getPlayerAttackPower();
    void setPlayerAttackPower(int attackPower);
    int getPlayerBulletCnt();
    void setPlayerBulletCnt(int bulletCnt);
    int getThunderCnt();
    void setThunderCnt(int missileCnt);
    int getShieldCnt();
    void setShieldCnt(int shieldCnt);
    PLAYER_AIRPLANE_SHAPE getPlayerAirplaneShape();
    void setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE shape);
    void enableShield();
    void enableThunder();
    void playerInitWhenStageBegin();
    void playCoinSound();

private:
    void spawnPlayerBullet(std::pair<float, float>& spawnPos);
    void turnOnShield();
    void turnOffShield();
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
    int thunderCnt = 0;
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