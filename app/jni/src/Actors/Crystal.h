#pragma once
#include "HActor.h"

class ImageComponent;
class CollisionBoxComponent;
class MovementComponent;

class Crystal :public HActor
{
public:
    Crystal();
    Crystal(const Crystal&) = delete;
    Crystal& operator=(const Crystal&) = delete;
    virtual ~Crystal() override;
    virtual void render() override;
    virtual void update(const float deltaTime) override;

private:
    ImageComponent* crystalImg = nullptr;
    CollisionBoxComponent* collisionBox = nullptr;
    MovementComponent* crystalMovement = nullptr;
    static const float destroyDistance;
};