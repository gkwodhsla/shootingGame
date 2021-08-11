#include "HPawn.h"
#include "../HPlayerController.h"
#include "../Components/MovementComponent.h"

HPawn::HPawn()
{
    movementComp = new MovementComponent(this);
}

HPawn::~HPawn()
{

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

}