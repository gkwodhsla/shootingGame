#pragma once

#include "HSceneComponent.h"

class SDL_Rect;

class CollisionBoxComponent :public HSceneComponent
{
public:
    CollisionBoxComponent() = delete;
    CollisionBoxComponent(int x, int y, int w, int h, HActor* owner);
    virtual ~CollisionBoxComponent();
    virtual void render() override;
    void update(float deltaTime) override;
    void setDrawDebugBox(bool canDraw);
    bool checkCollision(CollisionBoxComponent& otherRect);
public:
    void setWidthAndHeight(int w, int h);
private:
    int w = 0;
    int h = 0;
    bool canDrawDebugBox = false;
};