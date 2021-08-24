#pragma once
#include "HActor.h"

class ImageComponent;
class MovementComponent;
class CollisionBoxComponent;

enum class BULLET_COLOR
{
    GREEN,
    RED,
    PURPLE,
    BLUE,
    SKY
};

class Bullet : public HActor
{
public:
    Bullet() = delete;
    Bullet(const std::pair<float, float>& spawnPosition, BULLET_COLOR bulletColor,
           const Vector2D& dirVec);
    virtual ~Bullet();
    virtual void render();
    virtual void update(float deltaTime);
    void resetBulletToInitialState();
    void changeBulletSpeed(float speed);
    bool getIsPlayerBullet();

public:
    CollisionBoxComponent* getCollisionComp();

private:
    ImageComponent* bulletImg;
    MovementComponent* bulletMovement;
    CollisionBoxComponent* collisionBox;
    bool isPlayerBullet = false;
};
