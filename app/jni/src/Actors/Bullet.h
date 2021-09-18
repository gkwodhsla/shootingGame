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
    Bullet();
    Bullet(const std::pair<float, float>& spawnPosition, BULLET_COLOR bulletColor,
           const Vector2D& dirVec);
    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;
    virtual ~Bullet();
    virtual void render();
    virtual void update(const float deltaTime);
    void resetBulletToInitialState();
    void changeBulletSpeed(float speed);
    bool getIsPlayerBullet();
    void init(const std::pair<float, float> &spawnPosition, BULLET_COLOR bulletColor);

private:
    void initStaticData();

public:
    CollisionBoxComponent* getCollisionComp();

public:
    static ImageComponent* greenBulletImg;
    static ImageComponent* redBulletImg;
    static ImageComponent* purpleBulletImg;
    static ImageComponent* blueBulletImg;
    static ImageComponent* skyBulletImg;

private:
    ImageComponent* bulletImg;
    MovementComponent* bulletMovement;
    CollisionBoxComponent* collisionBox;
    bool isPlayerBullet = false;
};
