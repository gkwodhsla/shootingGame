#include "CollisionBoxComponent.h"
#include "../Framework.h"
#include <SDL.h>

CollisionBoxComponent::CollisionBoxComponent(int x, int y, int w, int h, HActor *owner)
{
    setOwner(owner);
    this->setComponentLocalLocation(std::make_pair(float(x), float(y)));
    this->w = w;
    this->h = h;
    this->setComponentLocalRotation(0.0f);

}

CollisionBoxComponent::~CollisionBoxComponent()
{
}

void CollisionBoxComponent::render()
{
    HSceneComponent::render();
    if(canDrawDebugBox)
    {
        SDL_SetRenderDrawColor(Framework::renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect temp;
        auto loc = getComponentWorldLocation();
        temp.x = loc.first;
        temp.y = loc.second;
        temp.w = w;
        temp.h = h;
        SDL_RenderDrawRect(Framework::renderer, &temp);
    }
}

void CollisionBoxComponent::update(float deltaTime)
{
    HSceneComponent::update(deltaTime);
}

void CollisionBoxComponent::setDrawDebugBox(bool canDraw)
{
    canDrawDebugBox = canDraw;
}

bool CollisionBoxComponent::checkCollision(CollisionBoxComponent& otherRect)
{
    SDL_Rect temp;
    auto loc = getComponentWorldLocation();
    temp.x = loc.first;
    temp.y = loc.second;
    temp.w = w;
    temp.h = h;

    auto otherRectLoc = otherRect.getComponentWorldLocation();

    SDL_Rect other;
    other.x = otherRectLoc.first;
    other.y = otherRectLoc.second;
    other.w = otherRect.w;
    other.h = otherRect.h;

    return SDL_HasIntersection(&temp, &other);
}

void CollisionBoxComponent::setWidthAndHeight(int w, int h)
{
    this->w = w;
    this->h = h;
}

