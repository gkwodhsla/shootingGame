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
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/Bullet.h"

Airplane::Airplane()
{
    rootComponent->setComponentLocalLocation(std::make_pair(Framework::rendererWidth / 2,
                                                            Framework::rendererHeight - 300));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);
    airplaneImg = new ImageComponent("image/player/1.png", std::make_pair(0, 0), this);
    airplaneImg->attachTo(rootComponent);

    auto airPlaneImgSize = airplaneImg->getImageSize();
    boosterSprite = new SpritesheetComponent("image/spritesheet/rocketFlame2.png",
                                             std::make_pair(airPlaneImgSize.first/2 - 13, airPlaneImgSize.second - 30),
                                             this, 2, 1, 2);
    boosterSprite->setDrawCntPerSec(8);
    boosterSprite->attachTo(airplaneImg);
    boosterSprite->setScale(std::make_pair(30,108));
    boosterSprite->setLooping(true);
    boosterSprite->setImageFlip(SDL_FLIP_VERTICAL);

    //explosionSprite = new SpritesheetComponent()
    //추후 추가 예정
}

Airplane::~Airplane()
{
    delete airplaneImg;
    airplaneImg = nullptr;

    delete boosterSprite;
    boosterSprite = nullptr;

    //delete explosionSprite;
    //explosionSprite = nullptr
    //추후 추가 예정
}

void Airplane::render()
{
    HPawn::render();
}

void Airplane::update(float deltaTime)
{
    HPawn::update(deltaTime);
    curFireTime -= deltaTime;
    if(curFireTime <= 0.0f)
    {
        auto imageSize = airplaneImg->getScale();
        auto loc = rootComponent->getComponentLocalLocation();
        loc.first += float(imageSize.first) / 2;
        spawnPlayerBullet(loc);
        curFireTime = fireRate;
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

void Airplane::spawnPlayerBullet(const std::pair<float, float>& spawnPos)
{
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    auto cont = mainLevel->playerBullets;
    for(int i = 0; i < mainLevel->playerBulletSize; ++i)
    {
        if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
        {
            cont[i]->setVisibility(true);
            cont[i]->setActorTickable(true);
            cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
            //__android_log_print(ANDROID_LOG_INFO, "SDL_Error",
               //                 "spawn using %d element", i);
            break;
        }
    }
}