//
// Created by lenovo on 2021-08-07.
//

#include "HPrimitiveComponent.h"

HPrimitiveComponent::HPrimitiveComponent()
{

}

HPrimitiveComponent::~HPrimitiveComponent()
{

}

void HPrimitiveComponent::update(float deltaTime)
{

}

void HPrimitiveComponent::render(SDL_Renderer *renderer)
{

}

void HPrimitiveComponent::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

void HPrimitiveComponent::setScale(std::pair<float, float>& scale)
{
    this->scale = scale;
}
const std::pair<float, float> HPrimitiveComponent::getScale()
{
    return scale;
}

const bool HPrimitiveComponent::getVisibility()
{
    return visibility;
}


