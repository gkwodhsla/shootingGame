#include "CollisionBoxComponent.h"
#include "../Framework.h"
#include <SDL.h>
#include "../GlobalFunction.h"
#include "../Level/HLevelBase.h"
#include "../Level/MainLevel.h"
#include <android/log.h>

using namespace GlobalFunction;

CollisionBoxComponent::CollisionBoxComponent(int x, int y, int w, int h, HActor *owner)
{
    setOwner(owner);
    this->setComponentLocalLocation(std::make_pair(float(x), float(y)));
    this->w = w;
    this->h = h;
    this->setComponentLocalRotation(0.0f);
    GetLevel()->addNewCollisionBoxToLevel(this);
    //충돌체크를 위해 레벨의 콜리전 박스 배열에 추가한다.
}

CollisionBoxComponent::~CollisionBoxComponent()
{
    GetLevel()->destroyBox(this);
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

void CollisionBoxComponent::update(const float deltaTime)
{
    HSceneComponent::update(deltaTime);
    if(Framework::curLevel == nullptr)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "not valid");
    }
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

    if(SDL_HasIntersection(&temp, &other)) //만약 충돌했다면 충돌한 두 액터에 이벤트 호출하라고 알려준다.
    {
        if(collisionResponse)
        {
            collisionResponse(otherRect.getOwner());
        }
        if(otherRect.collisionResponse)
        {
            otherRect.collisionResponse(this->getOwner());
        }
    }

    return false;
}

void CollisionBoxComponent::setWidthAndHeight(int w, int h)
{
    this->w = w;
    this->h = h;
}

void CollisionBoxComponent::registerCollisionResponse(std::function<void(HActor*)> func)
{
    collisionResponse = func;
}