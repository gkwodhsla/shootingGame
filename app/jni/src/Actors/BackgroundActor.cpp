//
// Created by lenovo on 2021-08-07.
//

#include "BackgroundActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
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
    camera->y = 0;
    camera->w = cameraWidthAndHeight;
    camera->h = cameraWidthAndHeight;
}

BackgroundActor::~BackgroundActor()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete backgroundImage;
    backgroundImage = nullptr;

    delete camera;
    camera = nullptr;
}

void BackgroundActor::render()
{
    rootComponent->render();

    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y + cameraWidthAndHeight >= bgImgSize.second)
    {
        auto yCoord =(float(Framework::rendererHeight)/float(cameraWidthAndHeight))*abs(bgImgSize.second - camera->y);
        backgroundImage->setComponentLocalLocation(std::make_pair(0, yCoord));
        backgroundImage->setScale(std::make_pair(Framework::rendererWidth, Framework::rendererHeight - yCoord + 10));
        backgroundImage->setClipRect(camera->x, camera->y - bgImgSize.second, camera->w, camera->h);



        backgroundImage->render();
    }
}

void BackgroundActor::update(float deltaTime)
{
    accYPos += 0.3f;
    if(accYPos>=1.0f)
    {
        accYPos = 0.0f;
        camera->y += 1;
    }
    backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
    backgroundImage->setScale(std::make_pair(Framework::rendererWidth, Framework::rendererHeight));
    backgroundImage->setClipRect(camera->x, camera->y, camera->w, camera->h);
    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y + cameraWidthAndHeight >= bgImgSize.second)
    {
        backgroundImage->setScale(std::make_pair(Framework::rendererWidth,
      (float(Framework::rendererHeight)/float(cameraWidthAndHeight))*abs(bgImgSize.second - camera->y)));
    }
    if(camera->y >= bgImgSize.second)
    {
        camera->y = 0;
    }
}

void BackgroundActor::changeBackgroundImage(const std::string& path)
{
    backgroundImage->changeImage(path);
}