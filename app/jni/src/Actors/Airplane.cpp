//
// Created by lenovo on 2021-08-11.
//

#include <SDL.h>
#include <android/log.h>
#include "Airplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Framework.h"

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

}

void Airplane::handleEvent(SDL_Event &e)
{
    auto imageSize = airplaneImg->getScale();

    if(e.type == SDL_FINGERDOWN)
    {
        rootComponent->setComponentLocalLocation
        (std::make_pair(e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
               e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));

        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                "height: %d", imageSize.second);
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
