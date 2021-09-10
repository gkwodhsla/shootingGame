#include "GlobalFunction.h"
#include "Framework.h"
#include "Level/HLevelBase.h"
#include "HPlayerController.h"
#include "Actors/HPawn.h"

HLevelBase* GlobalFunction::GetLevel()
{
    return Framework::curLevel;
}

HPlayerController* GlobalFunction::GetPlayerController()
{
    return Framework::curLevel->getPlayerController();
}

HPawn* GlobalFunction::GetPlayerPawn()
{
    return Framework::curLevel->getPlayerController()->getControlledPawn();
}