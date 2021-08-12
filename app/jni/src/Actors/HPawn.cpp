#include "HPawn.h"
#include "../HPlayerController.h"
#include "../Components/MovementComponent.h"

HPawn::HPawn()
{
    movementComp = new MovementComponent(this);
}

HPawn::~HPawn()
{
    delete movementComp;
    movementComp = nullptr;
}

void HPawn::setCanRecvInputEvent(bool canInput)
{

}

HPlayerController* HPawn::getController()
{
    return controller;
}

void HPawn::render()
{

}

void HPawn::update(float deltaTime)
{
    HActor::update(deltaTime);
}