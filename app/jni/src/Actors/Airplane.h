#pragma once

#include "HPawn.h"

class ImageComponent;
class SpritesheetComponent;

class Airplane :public HPawn
{
public:
    Airplane();
    virtual ~Airplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;

private:
    void spawnPlayerBullet(const std::pair<float, float>& spawnPos);

protected:
    ImageComponent* airplaneImg = nullptr;
    SpritesheetComponent* explosionSprite = nullptr;
    float fireRate = 0.5f;
    float curFireTime = 0.5f;

private:
    SpritesheetComponent* boosterSprite = nullptr;
};