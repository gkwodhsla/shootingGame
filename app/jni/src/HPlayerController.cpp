#include "HPlayerController.h"
#include "Actors/HPawn.h"

HPlayerController::HPlayerController(HPawn* controlledPawn)
{

}

HPlayerController::~HPlayerController()
{

}

void HPlayerController::possess(HPawn* pawn)
{
    controlledPawn = pawn;
}

void HPlayerController::unpossess()
{
    controlledPawn = nullptr;
}

void HPlayerController::changeInputMode(const INPUT_MODE inputMode)
{
    curInputMode = inputMode;
}

INPUT_MODE HPlayerController::getInputMode()
{
    return curInputMode;
}

void HPlayerController::handleEvent(const SDL_Event& e)
{
    if(controlledPawn)
    {
        controlledPawn->handleEvent(e);
    }
}

HPawn* HPlayerController::getControlledPawn()
{
    return controlledPawn;
}
