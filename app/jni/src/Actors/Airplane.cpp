//
// Created by lenovo on 2021-08-11.
//

#include <SDL.h>
#include <android/log.h>
#include <vector>
#include "Airplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/Bullet.h"

Airplane::Airplane()
{
    rootComponent = new HSceneComponent();
    rootComponent->setComponentLocalLocation(std::make_pair(Framework::rendererWidth / 2,
                                                            Framework::rendererHeight - 300));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);
    airplaneImg = new ImageComponent("image/player/1.png",std::make_pair(0, 0),this);
    airplaneImg->attachTo(rootComponent);
}

Airplane::~Airplane()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete airplaneImg;
    airplaneImg = nullptr;
}

void Airplane::render()
{
    rootComponent->render();
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
    auto imageSize = airplaneImg->getScale();

    if(e.type == SDL_FINGERDOWN)
    {
        rootComponent->setComponentLocalLocation
        (std::make_pair(e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
               e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
    }
    else if(e.type == SDL_FINGERMOTION)
    {
        rootComponent->setComponentLocalLocation
                (std::make_pair(e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
                                e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
    }
    else if(e.type == SDL_FINGERUP)
    {

    }
}

void Airplane::spawnPlayerBullet(const std::pair<float, float>& spawnPos)
{
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    auto cont = mainLevel->playerBullets;
    for(int i = 0; i < mainLevel->playerBulletSize; ++i)
    {
        if(!cont[i]->getVisibility())
        {
            cont[i]->setVisibility(true);
            cont[i]->setActorTickable(true);
            cont[i]->getRootComponent()->setComponentLocalLocation(spawnPos);
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "spawn using %d element", i);
            break;
        }
    }
}