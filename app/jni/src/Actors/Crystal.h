#pragma once
#include "HActor.h"

class ImageComponent;
class CollisionBoxComponent;
class MovementComponent;

class Crystal :public HActor
{
public:
    Crystal();
    virtual ~Crystal() override;
    virtual void render() override;
    virtual void update(float deltaTime) override;

private:
    ImageComponent* crystalImg = nullptr;
    CollisionBoxComponent* collisionBox = nullptr;
    MovementComponent* crystalMovement = nullptr;
};