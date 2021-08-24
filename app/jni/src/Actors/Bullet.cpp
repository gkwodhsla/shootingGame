#include "Bullet.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Framework.h"
#include "../Level/HLevelBase.h"
#include "../Level/MainLevel.h"
#include "../GlobalFunction.h"
#include "../Actors/EnemyAirplane.h"
#include <functional>
#include <android/log.h>

using namespace GlobalFunction;

Bullet::Bullet(const std::pair<float, float> &spawnPosition, BULLET_COLOR bulletColor,
               const Vector2D& dirVec)
{
    rootComponent->setComponentLocalLocation(spawnPosition);
    rootComponent->setComponentLocalRotation(0.0f);
    std::string path;
    if(bulletColor == BULLET_COLOR::GREEN)
    {
        path = "image/bullet/1.png";
        isPlayerBullet = true;
    }
    else if(bulletColor == BULLET_COLOR::RED)
    {
        path = "image/bullet/e2.png";
    }
    else if(bulletColor == BULLET_COLOR::PURPLE)
    {
        path = "image/bullet/e1.png";
    }
    else if(bulletColor == BULLET_COLOR::BLUE)
    {
        path = "image/bullet/e3.png";
    }
    else if(bulletColor == BULLET_COLOR::SKY)
    {
        path = "image/bullet/e4.png";
    }
    bulletImg = new ImageComponent(path, std::make_pair(0, 0), this);

    bulletImg->attachTo(rootComponent);

    bulletMovement = new MovementComponent(this);
    this->dirVec = dirVec;

    bulletMovement->setSpeed(900.0f);
    bulletMovement->setAcceleration(std::make_pair(dirVec.x * 1000.0f, dirVec.y * 1000.0f));

    auto imgSize = bulletImg->getScale();
    collisionBox = new CollisionBoxComponent(0, 0, imgSize.first, imgSize.second, this);
    collisionBox->setDrawDebugBox(true);

    collisionBox->attachTo(rootComponent);

    if(isPlayerBullet) //아군총알의 경우 적군과 충돌시 우선 버퍼에 반환해준다.
    {
        auto collisionResponse = [this](HActor* other) mutable
        {
            EnemyAirplane* enemy = Cast<EnemyAirplane>(other);

            if(enemy && enemy->getCanDamaged())
            {
                this->resetBulletToInitialState();
            }
        };
        collisionBox->registerCollisionResponse(collisionResponse);
    }

    lifeTime = 3.0f;
}

Bullet::~Bullet()
{
    delete bulletImg;
    bulletImg = nullptr;

    delete bulletMovement;
    bulletMovement = nullptr;

    delete collisionBox;
    collisionBox = nullptr;
}

void Bullet::render()
{
    HActor::render();
}

void Bullet::update(float deltaTime)
{
    HActor::update(deltaTime);
    if(tickable)
    {
        bulletMovement->update(deltaTime);
        if(isPendingToKill) // 해당총알이 수명이 다해 파괴예정이면 해당 버퍼를 사용할 수 있게 해준다.
        {
            resetBulletToInitialState();
        }
    }
}

void Bullet::resetBulletToInitialState()
{
    tickable = false;
    visibility = false;
    lifeTime = 3.0f;
    isPendingToKill = false;
}

CollisionBoxComponent* Bullet::getCollisionComp()
{
    return collisionBox;
}

void Bullet::changeBulletSpeed(float speed)
{
    bulletMovement->setSpeed(speed);
}

bool Bullet::getIsPlayerBullet()
{
    return isPlayerBullet;
}