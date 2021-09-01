#include "AirplaneController.h"
#include "UI/ShopCanvas.h"
#include "UI/InGameCanvas.h"
#include "UI/YesNoCanvas.h"
#include "UI/CashShopCanvas.h"
#include "UI/LoginCanvas.h"
#include "Framework.h"
#include "GlobalFunction.h"

using namespace GlobalFunction;

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
    yesNoCanvas = new YesNoCanvas(700, 600, (Framework::rendererWidth - 700) / 2, 300);
    testTitle = new LoginCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    testTitle->addToViewport();
    //shopCanvas->addToViewport();
}

void AirplaneController::changeShop()
{
    if(isShopCanvasShow)
    {
        shopCanvas->removeFromViewport();
        cashShopCanvas->addToViewport();
        isShopCanvasShow = false;
        auto curShopCanvas = Cast<ShopCanvas>(shopCanvas);
        auto curCashCanvas = Cast<CashShopCanvas>(cashShopCanvas);
        if(curShopCanvas && curCashCanvas)
        {
            curMoney = curShopCanvas->getCrystal();
            curCashCanvas->setCrystal(curMoney);
        }
    }
    else
    {
        shopCanvas->addToViewport();
        cashShopCanvas->removeFromViewport();
        isShopCanvasShow = true;
        auto curShopCanvas = Cast<ShopCanvas>(shopCanvas);
        auto curCashCanvas = Cast<CashShopCanvas>(cashShopCanvas);
        if(curShopCanvas && curCashCanvas)
        {
            curMoney = curCashCanvas->getCrystal();
            curShopCanvas->setCrystal(curMoney);
        }
    }
}

void AirplaneController::showYesNoWindow()
{
    yesNoCanvas->addToViewport();
}

int AirplaneController::getMoney()
{
    return curMoney;
}

void AirplaneController::setMoney(int newMoney)
{
    curMoney = newMoney;
}

void AirplaneController::processingBuyProtocol()
{
    auto curCashCanvas = Cast<CashShopCanvas>(cashShopCanvas);
    curCashCanvas->buyCrystal();
}