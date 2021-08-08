//
// Created by lenovo on 2021-08-07.
//

#include "BackgroundActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"

BackgroundActor::BackgroundActor()
{
    rootComponent = new HSceneComponent();
    rootComponent->setComponentLocalLocation(std::make_pair(0, 0));
    rootComponent->setComponentLocalRotation(0);

    backgroundImage = new ImageComponent("image/background/1.png", std::make_pair(0, 0));
    backgroundImage->attachTo(rootComponent);
}

BackgroundActor::~BackgroundActor()
{

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