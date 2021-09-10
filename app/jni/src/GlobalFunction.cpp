#include "GlobalFunction.h"
#include "Framework.h"
#include "Level/HLevelBase.h"
#include "HPlayerController.h"
#include "Actors/HPawn.h"

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> randomRot(0.0f, 30.0f);

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