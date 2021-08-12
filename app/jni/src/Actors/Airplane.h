#pragma once

#include "HPawn.h"

class ImageComponent;

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

private:
    ImageComponent* airplaneImg;
    float fireRate = 0.5f;
    float curFireTime = 0.5f;
};