#include "HPawn.h"
#include "../HPlayerController.h"
#include "../Components/MovementComponent.h"

HPawn::HPawn()
{
    movementComp = createComponent<MovementComponent>(this);
}

HPawn::~HPawn()
{

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

void HPawn::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(movementComp) //movementComp는 어디에도 붙지 않는다. 그렇기에 nullptr이 아니라면 update를 호출해준다.
    {
        movementComp->update(deltaTime);
    }
}