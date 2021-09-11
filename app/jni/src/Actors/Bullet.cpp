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
#include "../ActorObjectPool.h"
#include <functional>
#include <android/log.h>

using namespace GlobalFunction;

ImageComponent* Bullet::greenBulletImg = nullptr;
ImageComponent* Bullet::redBulletImg = nullptr;
ImageComponent* Bullet::purpleBulletImg = nullptr;
ImageComponent* Bullet::blueBulletImg = nullptr;
ImageComponent* Bullet::skyBulletImg = nullptr;

Bullet::Bullet()
{
    rootComponent->setComponentLocalLocation({0.0f, 0.0f});
    rootComponent->setComponentLocalRotation(0.0f);

    bulletImg = createComponent<ImageComponent>(this);
    bulletImg->attachTo(rootComponent);

    bulletMovement = createComponent<MovementComponent>(this);
    bulletMovement->setSpeed(900.0f);
    bulletMovement->setAcceleration(std::make_pair(dirVec.x * 1000.0f, dirVec.y * 1000.0f));

    this->dirVec = Vector2D(0.0f, 0.0f);

    auto imgSize = bulletImg->getScale();
    collisionBox = createComponent<CollisionBoxComponent>(0, 0, imgSize.first, imgSize.second, this);
    collisionBox->setDrawDebugBox(true);

    collisionBox->attachTo(rootComponent);

    setLifeTime(3.0f);

    auto customDestroyAction = [this]() mutable
    {
        auto mainLevel = Cast<MainLevel>(Framework::curLevel);
        mainLevel->bulletPool->returnToPool(this);
        setLifeTime(3.0f);
    };
    registerFuncWhenActorLifeTimeZero(customDestroyAction);
    initStaticData();
}

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
    bulletImg = createComponent<ImageComponent>(path, std::make_pair(0, 0), this);

    bulletImg->attachTo(rootComponent);

    bulletMovement = createComponent<MovementComponent>(this);
    this->dirVec = dirVec;

    bulletMovement->setSpeed(900.0f);
    bulletMovement->setAcceleration(std::make_pair(dirVec.x * 1000.0f, dirVec.y * 1000.0f));

    auto imgSize = bulletImg->getScale();
    collisionBox = createComponent<CollisionBoxComponent>(0, 0, imgSize.first, imgSize.second, this);
    collisionBox->setDrawDebugBox(true);

    collisionBox->attachTo(rootComponent);

    setLifeTime(3.0f);

    auto customDestroyAction = [this]() mutable
    {
        auto mainLevel = Cast<MainLevel>(Framework::curLevel);
        mainLevel->bulletPool->returnToPool(this);
        setLifeTime(3.0f);
    };
    registerFuncWhenActorLifeTimeZero(customDestroyAction);

    initStaticData();
}

Bullet::~Bullet()
{

}

void Bullet::render()
{
    HActor::render();
}

void Bullet::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(tickable)
    {
        bulletMovement->update(deltaTime);
    }
}

void Bullet::resetBulletToInitialState()
{
    auto mainLevel = Cast<MainLevel>(Framework::curLevel);
    mainLevel->bulletPool->returnToPool(this);
    setLifeTime(3.0f);
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

void Bullet::init(const std::pair<float, float> &spawnPosition, BULLET_COLOR bulletColor)
{
    rootComponent->setComponentLocalLocation(spawnPosition);

    std::string path;
    isPlayerBullet = false;
    ImageComponent* refImg = nullptr;
    if(bulletColor == BULLET_COLOR::GREEN)
    {
        refImg = Bullet::greenBulletImg;
        path = "image/bullet/1.png";
        isPlayerBullet = true;
    }
    else if(bulletColor == BULLET_COLOR::RED)
    {
        refImg = Bullet::redBulletImg;
        path = "image/bullet/e2.png";
    }
    else if(bulletColor == BULLET_COLOR::PURPLE)
    {
        refImg = Bullet::purpleBulletImg;
        path = "image/bullet/e1.png";
    }
    else if(bulletColor == BULLET_COLOR::BLUE)
    {
        refImg = Bullet::blueBulletImg;
        path = "image/bullet/e3.png";
    }
    else if(bulletColor == BULLET_COLOR::SKY)
    {
        refImg = Bullet::skyBulletImg;
        path = "image/bullet/e4.png";
    }

    //bulletImg->changeImage(path);
    bulletImg->referencingOtherImgCompsImg(*refImg);

    auto imgSize = bulletImg->getScale();

    collisionBox->setWidthAndHeight(imgSize.first, imgSize.second);

    setLifeTime(3.0f);
}

void Bullet::initStaticData()
{
    if(Bullet::greenBulletImg == nullptr)
    {
        Bullet::greenBulletImg = createComponent<ImageComponent>("image/bullet/1.png",std::make_pair(0,0),nullptr);
    }
    if(Bullet::redBulletImg == nullptr)
    {
        Bullet::redBulletImg = createComponent<ImageComponent>("image/bullet/e2.png",std::make_pair(0,0),nullptr);
    }
    if(Bullet::purpleBulletImg == nullptr)
    {
        Bullet::purpleBulletImg = createComponent<ImageComponent>("image/bullet/e1.png",std::make_pair(0,0),nullptr);
    }
    if(Bullet::blueBulletImg == nullptr)
    {
        Bullet::blueBulletImg = createComponent<ImageComponent>("image/bullet/e3.png",std::make_pair(0,0),nullptr);
    }
    if(Bullet::skyBulletImg == nullptr)
    {
        Bullet::skyBulletImg = createComponent<ImageComponent>("image/bullet/e4.png",std::make_pair(0,0),nullptr);
    }
}