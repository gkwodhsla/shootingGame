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
    rootComponent->setComponentLocalLocation(std::make_pair(100, 300));
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
    //e.tfinger.x
    //e.tfinger.y
    if(e.type == SDL_FINGERDOWN)
    {
        rootComponent->setComponentLocalLocation(std::make_pair(e.tfinger.x * Framework::rendererWidth,
                                                                e.tfinger.y * Framework::rendererHeight));
    }
    else if(e.type == SDL_FINGERMOTION)
    {
        rootComponent->setComponentLocalLocation(std::make_pair(e.tfinger.x * Framework::rendererWidth,
                                                                e.tfinger.y * Framework::rendererHeight));
    }
    else if(e.type == SDL_FINGERUP)
    {

    }
}
