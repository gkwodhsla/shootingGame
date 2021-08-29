#include "AirplaneController.h"
#include "UI/ShopCanvas.h"
#include "UI/InGameCanvas.h"
#include "UI/CashShopCanvas.h"
#include "Framework.h"

AirplaneController::AirplaneController(HPawn* controlledPawn):
HPlayerController(controlledPawn)
{

}

AirplaneController::~AirplaneController()
{

}

void AirplaneController::createCanvases()
{
    shopCanvas = new ShopCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    inGameCanvas = new InGameCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    cashShopCanvas = new CashShopCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);

    shopCanvas->addToViewport();
}