#pragma once

#include "HPawn.h"

class ImageComponent;
class SpritesheetComponent;
class CollisionBoxComponent;
class AudioComponent;

class AirplaneParent: public HPawn
{
public:
    AirplaneParent();
    AirplaneParent(const AirplaneParent&) = delete;
    AirplaneParent& operator=(const AirplaneParent&) = delete;
    virtual ~AirplaneParent();
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    virtual void handleEvent(const SDL_Event& e) override;
    void setIsDie(bool isDie);
    bool getIsDie();
    void setFireRate(float rate);
protected:
    ImageComponent* airplaneImg = nullptr;
    SpritesheetComponent* explosionSprite = nullptr;
    CollisionBoxComponent* collisionBox = nullptr;
    AudioComponent* explosionAudio = nullptr;
    float fireRate = 0.5f;
    float curFireTime = 0.5f;
    bool isDie = false;
};