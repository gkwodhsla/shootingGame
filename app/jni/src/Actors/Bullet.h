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
    //오브젝트 풀에서 객체를 꺼내면 이 함수를 호출해서 초기화한다.

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
    //총알 이미지를 모두 로드하지 않고 static으로 번갈아 쓴다.
    static int playerBulletWidth;

private:
    ImageComponent* bulletImg;
    MovementComponent* bulletMovement;
    CollisionBoxComponent* collisionBox;
    bool isPlayerBullet = false;
};
