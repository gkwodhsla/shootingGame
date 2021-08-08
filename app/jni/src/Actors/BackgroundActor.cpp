//
// Created by lenovo on 2021-08-07.
//

#include "BackgroundActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include <utility>

BackgroundActor::BackgroundActor()
{
    rootComponent = new HSceneComponent();
    rootComponent->setComponentLocalLocation(std::make_pair(0, 0));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);

    backgroundImage = new ImageComponent("image/background/4.png", std::make_pair(0, 0), this);
    backgroundImage->attachTo(rootComponent);
    backgroundImage->setScale(std::make_pair(2.0f, 2.0f));
}

BackgroundActor::~BackgroundActor()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete backgroundImage;
    backgroundImage = nullptr;
}

void BackgroundActor::render()
{
    rootComponent->render();
}

void BackgroundActor::update()
{

}

void BackgroundActor::changeBackgroundImage(const std::string& path)
{
    backgroundImage->changeImage(path);
}