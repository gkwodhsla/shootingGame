#include "TitleController.h"
#include "UI/LoginCanvas.h"
#include "Level/MainLevel.h"
#include "Framework.h"

TitleController::TitleController(HPawn* controlledPawn):
HPlayerController(controlledPawn)
{
    changeInputMode(INPUT_MODE::UI_ONLY);
    loginCanvas = new LoginCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    loginCanvas->addToViewport();
}

TitleController::~TitleController()
{
    Framework::eraseCanvas(loginCanvas);
    //원래는 안 지워도 게임 종료시 프레임워크에서 일괄 제거를 하지만
    //다음 레벨로 넘어가는데 굳~~이 존재할 필요가 없기 때문에 지워준다.
}

void TitleController::goToMainLevel()
{
    auto newLevel = new MainLevel();
    Framework::changeLevel(newLevel);
}
