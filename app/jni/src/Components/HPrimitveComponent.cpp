//
// Created by lenovo on 2021-08-07.
//

#include "HPrimitveComponent.h"

HPrimitveComponent::HPrimitveComponent()
{

}

HPrimitveComponent::~HPrimitveComponent()
{

}

void HPrimitveComponent::update(float deltaTime)
{

}

void HPrimitveComponent::Render(SDL_Renderer *renderer)
{

}

void HPrimitveComponent::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

const bool HPrimitveComponent::getVisibility()
{
    return visibility;
}


