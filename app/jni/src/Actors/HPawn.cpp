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
    canReceiveInputFromPlayer = canInput;
}

HPlayerController* HPawn::getController()
{
    return controller;
}

void HPawn::render()
{
    HActor::render();
}

void HPawn::update(float deltaTime)
{
    HActor::update(deltaTime);
    if(movementComp) //movementComp는 어디에도 붙지 않는다. 그렇기에 nullptr이 아니라면 update를 호출해준다.
    {
        movementComp->update(deltaTime);
    }
}