#pragma once

#include "HSceneComponent.h"
#include <functional>

class SDL_Rect;
class HActor;

class CollisionBoxComponent :public HSceneComponent
{
public:
    CollisionBoxComponent() = delete;
    CollisionBoxComponent(const CollisionBoxComponent&) = delete;
    CollisionBoxComponent& operator=(const CollisionBoxComponent&) = delete;
    CollisionBoxComponent(int x, int y, int w, int h, HActor* owner);
    virtual ~CollisionBoxComponent();
    virtual void render() override;
    void update(const float deltaTime) override;
    void setDrawDebugBox(bool canDraw);
    bool checkCollision(CollisionBoxComponent& otherRect);
public:
    void setWidthAndHeight(int w, int h);
    std::function<void(HActor*)> collisionResponse = nullptr;
    void registerCollisionResponse(std::function<void(HActor*)> func);
private:
    int w = 0;
    int h = 0;
    bool canDrawDebugBox = false;
};