//
// Created by lenovo on 2021-08-10.
//

#include "HPlayerController.h"
#include "Actors/HPawn.h"

HPlayerController::HPlayerController()
{

}

HPlayerController::~HPlayerController()
{

}

void HPlayerController::possess(HPawn* pawn)
{
    controlledPawn = pawn;
}

void HPlayerController::changeInputMode(INPUT_MODE inputMode)
{
    curInputMode = inputMode;
}

void HPlayerController::handleEvent()
{

}

HPawn* HPlayerController::getControlledPawn()
{
    return controlledPawn;
}
