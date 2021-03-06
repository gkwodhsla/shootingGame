#include "BackgroundActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Components/AmbientMusicComponent.h"
#include "../Framework.h"
#include <utility>
#include <SDL.h>
#include <cmath>
#include <android/log.h>

BackgroundActor::BackgroundActor()
{
    rootComponent->setComponentLocalLocation(std::make_pair(0, 0));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);

    backgroundImage = createComponent<ImageComponent>("image/background/2.png", std::make_pair(0, 0), this);
    backgroundImage->attachTo(rootComponent);
    backgroundImage->setClipDraw(true);

    battleMusic = createComponent<AmbientMusicComponent>("sound/battleAmbient.mp3", 255, this);
    shopMusic = createComponent<AmbientMusicComponent>("sound/shopAmbient.mp3", 255, this);

    auto bgImgSize = backgroundImage->getImageSize();
    backgroundImage->setScale(std::make_pair(Framework::RTWidth, Framework::RTHeight));
    __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                        "RendererWidth:%d, RendererHeight:%d", Framework::rendererWidth, Framework::rendererHeight);
    camera = new SDL_Rect();
    camera->x = 0;
    camera->y = bgImgSize.second - cameraWidthAndHeight;
    camera->w = cameraWidthAndHeight;
    camera->h = cameraWidthAndHeight;

    accYPos = bgImgSize.second - cameraWidthAndHeight;

    dirVec.x = 0;
    dirVec.y = -1.0f;
}

BackgroundActor::~BackgroundActor()
{
    delete camera;
    camera = nullptr;
}

void BackgroundActor::render()
{
    HActor::render();
    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y <= 0)
    {
        float ratio = float(Framework::RTHeight) / float(cameraWidthAndHeight);
        backgroundImage->setClipRect(camera->x, bgImgSize.second + camera->y,
                                     cameraWidthAndHeight, abs(camera->y));
        backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
        backgroundImage->setScale(std::make_pair(Framework::RTWidth, ratio * abs(camera->y)));

        backgroundImage->render();
    }
    //infinite scrolling ????????? ?????? clipRect??? ?????? ????????? ???????????? ??????????????? ????????? ??? ??? ??? ????????? ??????.
}

void BackgroundActor::update(const float deltaTime)
{
    HActor::update(deltaTime);
    accYPos = accYPos + velocity * deltaTime + (0.5f * acceleration * deltaTime*deltaTime);
    camera->y = int(accYPos);

    backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
    backgroundImage->setScale(std::make_pair(Framework::RTWidth, Framework::RTHeight));
    backgroundImage->setClipRect(camera->x, camera->y, cameraWidthAndHeight, cameraWidthAndHeight);

    auto bgImgSize = backgroundImage->getImageSize();
    if(camera->y <= 0)
    {
        float ratio = float(Framework::RTHeight) / float(cameraWidthAndHeight);
        backgroundImage->setClipRect(camera->x, 0, cameraWidthAndHeight,
                                     cameraWidthAndHeight + camera->y);
        backgroundImage->setScale(std::make_pair(Framework::RTWidth, 10 + Framework::RTHeight -
                                                                           (ratio * abs(camera->y))));
        backgroundImage->setComponentLocalLocation(std::make_pair(0, abs(ratio * abs(camera->y))));
    }

    if(camera->y + cameraWidthAndHeight <= 10)
    {
        camera->y = bgImgSize.second - cameraWidthAndHeight;
        accYPos = bgImgSize.second - cameraWidthAndHeight;

        backgroundImage->setComponentLocalLocation(std::make_pair(0, 0));
        backgroundImage->setScale(std::make_pair(Framework::RTWidth, Framework::RTHeight));
        backgroundImage->setClipRect(camera->x, camera->y, cameraWidthAndHeight, cameraWidthAndHeight);
    }
}

void BackgroundActor::changeBackgroundImage(const std::string& path)
{
    backgroundImage->changeImage(path);
}

void BackgroundActor::playBattleMusic()
{
    shopMusic->stop();
    battleMusic->play();
}

void BackgroundActor::stopBattleMusic()
{
    battleMusic->stop();
    shopMusic->play();
}