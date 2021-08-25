//
// Created by lenovo on 2021-08-11.
//

#include <SDL.h>
#include <android/log.h>
#include <vector>
#include "Airplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../ActorObjectPool.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/Bullet.h"
#include "../GlobalFunction.h"

using namespace GlobalFunction;

Airplane::Airplane()
{
    rootComponent->setComponentLocalLocation(std::make_pair(Framework::rendererWidth / 2,
                                                            Framework::rendererHeight - 300));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);
    airplaneImg = new ImageComponent("image/player/1.png", std::make_pair(0, 0), this);
    airplaneImg->attachTo(rootComponent);
    airplaneImg->setScale({100, 115});

    auto airPlaneImgSize = airplaneImg->getScale();
    boosterSprite = new SpritesheetComponent("image/spritesheet/rocketFlame2.png",
                                             std::make_pair(airPlaneImgSize.first/2 - 13, airPlaneImgSize.second - 30),
                                             this, 2, 1, 2);
    boosterSprite->setDrawCntPerSec(8);
    boosterSprite->attachTo(airplaneImg);
    boosterSprite->setScale(std::make_pair(30,108));
    boosterSprite->setLooping(true);
    boosterSprite->setImageFlip(SDL_FLIP_VERTICAL);
    boosterSprite->play();

    explosionSprite = new SpritesheetComponent("image/spritesheet/explosion.png",
                                               std::make_pair(-80.0f, -45.0f), this, 24, 6, 4);
    explosionSprite->attachTo(rootComponent);
    explosionSprite->setScale(std::make_pair(350, 350));
    explosionSprite->setLooping(false);
    explosionSprite->setDrawCntPerSec(40);

    collisionBox = new CollisionBoxComponent(0, 0, airPlaneImgSize.first, airPlaneImgSize.second, this);
    collisionBox->setDrawDebugBox(true);
    collisionBox->attachTo(rootComponent);

    //explosionSprite = new SpritesheetComponent()
    //추후 추가 예정
}

Airplane::~Airplane()
{
    delete airplaneImg;
    airplaneImg = nullptr;

    delete boosterSprite;
    boosterSprite = nullptr;

    delete collisionBox;
    collisionBox = nullptr;

    delete explosionSprite;
    explosionSprite = nullptr;
    //추후 추가 예정
}

void Airplane::render()
{
    HPawn::render();
}

void Airplane::update(float deltaTime)
{
    HPawn::update(deltaTime);
    if(tickable)
    {
        curFireTime -= deltaTime;
        if (curFireTime <= 0.0f)
        {
            auto imageSize = airplaneImg->getScale();
            auto loc = rootComponent->getComponentLocalLocation();
            loc.first += float(imageSize.first) / 2 - float((bulletCnt - 1) * 20);
            spawnPlayerBullet(loc);
            curFireTime = fireRate;
        }
    }
}

void Airplane::handleEvent(SDL_Event &e)
{
    if(canReceiveInputFromPlayer) //플레이어 입력을 받을 수 있을때만 동작하게 한다.
    {
        auto imageSize = airplaneImg->getScale();

        if (e.type == SDL_FINGERDOWN)
        {
            rootComponent->setComponentLocalLocation
                    (std::make_pair(
                            e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
                            e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
        }
        else if (e.type == SDL_FINGERMOTION)
        {
            rootComponent->setComponentLocalLocation
                    (std::make_pair(
                            e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
                            e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
        }
        else if (e.type == SDL_FINGERUP)
        {

        }
    }
}

CollisionBoxComponent* Airplane::getCollisionBoxComp()
{
    return collisionBox;
}

int Airplane::getPlayerAttackPower()
{
    return attackPower;
}

void Airplane::setFireRate(float rate)
{
    fireRate = rate;
}

void Airplane::setPlayerAttackPower(int attackPower)
{
    this->attackPower = attackPower;
}

int Airplane::getPlayerBulletCnt()
{
    return bulletCnt;
}

void Airplane::setPlayerBulletCnt(int bulletCnt)
{
    this->bulletCnt = bulletCnt;
}

int Airplane::getMissileCnt()
{
    return missileCnt;
}

void Airplane::setMissileCnt(int missileCnt)
{
    this->missileCnt = missileCnt;
}

int Airplane::getShieldCnt()
{
    return shieldCnt;
}

void Airplane::setShieldCnt(int shieldCnt)
{
    this->shieldCnt = shieldCnt;
}

PLAYER_AIRPLANE_SHAPE Airplane::getPlayerAirplaneShape()
{
    return shape;
}

void Airplane::setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE shape)
{
    this->shape = shape;
    switch (this->shape)
    {
        case PLAYER_AIRPLANE_SHAPE::SHAPE2:
            airplaneImg->changeImage("image/player/2.png");
            airplaneImg->setScale({100, 115});
            break;

        case PLAYER_AIRPLANE_SHAPE::SHAPE3:
            airplaneImg->changeImage("image/player/3.png");
            airplaneImg->setScale({100, 115});
            break;
    }
}


void Airplane::turnOffBooster()
{
    boosterSprite->setVisibility(false);
}

void Airplane::spawnPlayerBullet(std::pair<float, float>& spawnPos)
{
    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
    auto cont = mainLevel->bulletPool;

    for(int i = bulletCnt; i > 0; --i)
    {
        auto bullet = cont->acquireObject();
        bullet->init(spawnPos, BULLET_COLOR::GREEN);
        bullet->setActorDirectionalVector({0.0f, -1.0f});
        bullet->changeBulletSpeed(900.0f);
        spawnPos.first += 20.0f;
    }

    /*int curSpawnBulletCnt = bulletCnt;
    for(int i = 0; i < mainLevel->playerBulletSize; ++i)
    {
        if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
        {
            cont[i]->setVisibility(true);
            cont[i]->setActorTickable(true);
            cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
            --curSpawnBulletCnt;
            if(curSpawnBulletCnt == 0)
                break;
            spawnPos.first += 20.0f;
            //__android_log_print(ANDROID_LOG_INFO, "SDL_Error",
               //                 "spawn using %d element", i);
        }
    }*/
}

