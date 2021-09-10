#include "HPrimitiveComponent.h"

HPrimitiveComponent::HPrimitiveComponent()
{
    componentTag = "HPrimitiveComponent";
}

HPrimitiveComponent::~HPrimitiveComponent()
{

}

void HPrimitiveComponent::update(const float deltaTime)
{
    HSceneComponent::update(deltaTime);
}

void HPrimitiveComponent::render()
{
    HSceneComponent::render();
}

void HPrimitiveComponent::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

void HPrimitiveComponent::setScale(const std::pair<int, int>& scale)
{
    this->scale = scale;
}
std::pair<int, int> HPrimitiveComponent::getScale()
{
    return scale;
}

bool HPrimitiveComponent::getVisibility()
{
    return visibility;
}


