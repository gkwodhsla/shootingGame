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
    setID(GlobalFunction::GetClassTypeUniqueID<AirplaneController>());
}

AirplaneController::~AirplaneController()
{

}

void AirplaneController::createCanvases()
{
    shopCanvas = Canvas::makeCanvas<ShopCanvas>(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    inGameCanvas = Canvas::makeCanvas<InGameCanvas>(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    cashShopCanvas = Canvas::makeCanvas<CashShopCanvas>(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    yesNoCanvas = Canvas::makeCanvas<YesNoCanvas>(Framework::rendererWidth / 2, Framework::rendererHeight / 3,
                                  (Framework::rendererWidth - Framework::rendererWidth / 2) / 2, 200);
    shopCanvas->addToViewport();
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
    auto curShopCanvas = Cast<ShopCanvas>(shopCanvas);
    auto curCashCanvas = Cast<CashShopCanvas>(cashShopCanvas);
    curCashCanvas->buyCrystal();
    if(curShopCanvas && curCashCanvas)
    {
        curMoney = curCashCanvas->getCrystal();
        curShopCanvas->setCrystal(curMoney);
    }
}