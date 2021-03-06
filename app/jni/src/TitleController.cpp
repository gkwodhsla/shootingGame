#include "TitleController.h"
#include "UI/LoginCanvas.h"
#include "Level/MainLevel.h"
#include "Framework.h"

TitleController::TitleController(HPawn* controlledPawn):
HPlayerController(controlledPawn)
{
    changeInputMode(INPUT_MODE::UI_ONLY);
    loginCanvas = GlobalFunction::makeCanvas<LoginCanvas>(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    loginCanvas->addToViewport();
}

TitleController::~TitleController()
{
    loginCanvas->removeFromViewport();
}

void TitleController::goToMainLevel()
{
    auto newLevel = GlobalFunction::createNewObject<MainLevel>();
    Framework::changeLevel(newLevel);
}
