#pragma once
#include "HActor.h"

class ImageComponent;
class MovementComponent;

enum class BULLET_COLOR
{
    GREEN,
    RED,
    PURPLE
};

class Bullet : public HActor
{
public:
    Bullet() = delete;
    Bullet(const std::pair<float, float>& spawnPosition, BULLET_COLOR bulletColor,
           const std::pair<float, float>& dirVec);
    virtual ~Bullet();
    virtual void render();
    virtual void update(float deltaTime);
private:
    ImageComponent* bulletImg;
    MovementComponent* bulletMovement;
};
