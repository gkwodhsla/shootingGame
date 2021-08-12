//
// Created by lenovo on 2021-08-07.
//

#include "BackgroundActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Components/MovementComponent.h"
#include "../Framework.h"
#include <utility>
#include <SDL.h>
#include <cmath>
#include <android/log.h>

BackgroundActor::BackgroundActor()
{
    rootComponent = new HSceneComponent();
    rootComponent->setComponentLocalLocation(std::make_pair(0, 0));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);

    //init imageComponent;
    backgroundImage = new ImageComponent("image/background/2.png", std::make_pair(0, 0), this);
    backgroundImage->attachTo(rootComponent);
    backgroundImage->setClipDraw(true);
    //init camera
    auto bgImgSize = backgroundImage->getImageSize();
    auto windowSize = Framework::screenRect;
    backgroundImage->setScale(std::make_pair(Framework::rendererWidth, Framework::rendererHeight));
    __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                        "width:%d, height:%d", Framework::rendererWidth, Framework::rendererHeight);
    camera = new SDL_Rect();
    camera->x = 0;
    camera->y = bgImgSize.second - cameraWidthAndHeight;
    camera->w = cameraWidthAndHeight;
    camera->h = cameraWidthAndHeight;

    bgMovement = new MovementComponent(this);
    dirVec = std::make_pair(0, -1.0f);
    bgMovement->setInitialVelocity(std::make_pair(0.0f, dirVec.second * 500.0f));
    bgMovement->setAcceleration(std::make_pair(0.0f, dirVec.second * 500.0f));
}

BackgroundActor::~BackgroundActor()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete backgroundImage;
    backgroundImage = nullptr;

    delete camera;
    camera = nullptr;

    delete bgMovement;
    bgMovement = nullptr;
}

void BackgroundActor::render()
{
    HActor::render();

    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y <= 0)
    {
        float ratio = float(Framework::rendererHeight) / float(cameraWidthAndHeight);
        backgroundImage->setClipRect(camera->x, bgImgSize.second + camera->y,
                                     cameraWidthAndHeight, abs(camera->y));
        backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
        backgroundImage->setScale(std::make_pair(Framework::rendererWidth, ratio * abs(camera->y)));

        backgroundImage->render();
    }
}

void BackgroundActor::update(float deltaTime)
{
    accYPos += 0.3f;
    if(accYPos>=1.0f)
    {
        accYPos = 0.0f;
        camera->y -= 1;
    }
    backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
    backgroundImage->setScale(std::make_pair(Framework::rendererWidth, Framework::rendererHeight));
    backgroundImage->setClipRect(camera->x, camera->y, cameraWidthAndHeight, cameraWidthAndHeight);

    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y <= 0)
    {
        float ratio = float(Framework::rendererHeight) / float(cameraWidthAndHeight);
        backgroundImage->setClipRect(camera->x, 0, cameraWidthAndHeight,
                                     cameraWidthAndHeight + camera->y);
        backgroundImage->setScale(std::make_pair(Framework::rendererWidth, 10 + Framework::rendererHeight -
                                                                           (ratio * abs(camera->y))));
        backgroundImage->setComponentLocalLocation(std::make_pair(0, abs(ratio * abs(camera->y))));
    }

    if(camera->y + cameraWidthAndHeight <= 0)
    {
        camera->y = bgImgSize.second - cameraWidthAndHeight;
    }
}

void BackgroundActor::changeBackgroundImage(const std::string& path)
{
    backgroundImage->changeImage(path);
}