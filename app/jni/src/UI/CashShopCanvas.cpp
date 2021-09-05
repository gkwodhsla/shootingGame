#include "CashShopCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "../AirplaneController.h"
#include "../GlobalFunction.h"
#include <string>
#include <vector>
#include <array>

using namespace GlobalFunction;

const int CashShopCanvas::sellItemNum = 6;
const std::array<std::string, 6> CashShopCanvas::crystalNums = {"100", "525", "1080", "3300", "5600", "11500"};
const std::array<std::string, 6> CashShopCanvas::prices = {"0.99$", "4.99$", "9.99$", "29.99$", "49.99$", "99.99$"};
CashShopCanvas::CashShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY):
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    initWindowImageWidgets();
    initButtonWidgets();
    initTextWidgets();
}

CashShopCanvas::~CashShopCanvas()
{

}

void CashShopCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender();
    }
}

void CashShopCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

bool CashShopCanvas::handleEvent(SDL_Event &e)
{
    return Canvas::handleEvent(e);
}

void CashShopCanvas::update(float deltaTime)
{
    Canvas::update(deltaTime);
}

void CashShopCanvas::updateCrystalText()
{
    moneyText->changeText(std::to_string(curCrystal));
    auto moneyTextScale = moneyText->getScale();
    moneyText->setLocalPosition(RTWidth - 250 + (200 - moneyTextScale.first) / 2,
                                40 + (moneyWindowImage->getScale().second - moneyTextScale.second) / 2);
}

int CashShopCanvas::getCrystal()
{
    return curCrystal;
}

void CashShopCanvas::setCrystal(int crystal)
{
    curCrystal = crystal;
    updateCrystalText();
}

void CashShopCanvas::buyCrystal()
{
    curCrystal += std::stoi(crystalNums[static_cast<int>(whichSelected)]);
    updateCrystalText();
}

WHICH_CASH_SELECTED CashShopCanvas::getWhichCashItemSelected()
{
    return whichSelected;
}

void CashShopCanvas::initWindowImageWidgets()
{
    bgImg = makeWidget<ImageWidget>("image/UIImage/window.png", this);
    bgImg->setLocalPosition(0, 0);
    bgImg->setScale(RTWidth, RTHeight, true);

    shopTitleImage = makeWidget<ImageWidget>("image/UIImage/Header.png", this);
    shopTitleImage->setLocalPosition(RTWidth / 2 - 150, 40);
    shopTitleImage->setScale(300, 120);

    crystalImage = makeWidget<ImageWidget>("image/UIImage/crystal.png", this);
    crystalImage->setLocalPosition(RTWidth - 340, 35);
    crystalImage->setScale(90, 110);

    moneyWindowImage = makeWidget<ImageWidget>("image/UIImage/box.png", this);
    moneyWindowImage->setLocalPosition(RTWidth - 250, 40);
    moneyWindowImage->setScale(200, 110);

    int smallWindowXSize = 350;
    int smallWindowYSize = 350;
    int curX = 100;
    int curY = -smallWindowYSize + 200;
    for(int i = 0; i < sellItemNum; ++i)
    {
        if(i%2 == 0)
        {
            curX = 100;
            curY += smallWindowYSize + 100;
        }
        else
        {
            curX = RTWidth - 100 - smallWindowYSize;
        }
        smallWindows.emplace_back(makeWidget<ImageWidget>("image/UIImage/smallWindow.png", this));
        smallWindows[i]->setScale(smallWindowXSize, smallWindowYSize);
        smallWindows[i]->setLocalPosition(curX, curY);

        crystals.emplace_back(makeWidget<ImageWidget>("image/UIImage/crystal" + std::to_string(i+1) + ".png", this));
        crystals[i]->setScale(150, 150);
        crystals[i]->setLocalPosition(curX + (smallWindowXSize / 2 - 75), curY + smallWindowYSize / 2 - 100);
    }
}

void CashShopCanvas::initButtonWidgets()
{
    int smallWindowXSize = 350;
    int smallWindowYSize = 350;
    int curX = 100;
    int curY = -smallWindowYSize + 200;
    for(int i = 0; i < sellItemNum; ++i)
    {
        if(i%2 == 0)
        {
            curX = 100;
            curY += smallWindowYSize + 100;
        }
        else
        {
            curX = RTWidth - 100 - smallWindowYSize;
        }
        buyButtons.emplace_back(makeWidget<ButtonWidget>("image/UIImage/downButton.png","image/UIImage/upButton.png",
                                                 "", "sound/click.wav", this));
        buyButtons[i]->setScale(180, 80);
        buyButtons[i]->setLocalPosition(curX + smallWindowXSize / 2 - 90,
                                        crystals[i]->getLocalPosition().second + crystals[i]->getScale().second);
        buyButtons[i]->buttonUpEvent = [=]()
        {
            auto PC = Cast<AirplaneController>(GetPlayerController());
            if(PC)
            {
                whichSelected = static_cast<WHICH_CASH_SELECTED>(i);
                PC->showYesNoWindow();
            }
        };
    }
    changeButton = makeWidget<ButtonWidget>("image/UIImage/changeDownButton.png","image/UIImage/changeUpButton.png",
                                    "", "sound/click.wav", this);
    changeButton->setScale(120, 120);
    changeButton->setLocalPosition(100, 35);
    changeButton->buttonUpEvent = []()
    {
        auto PC = Cast<AirplaneController>(GetPlayerController());
        PC->changeShop();
    };
}

void CashShopCanvas::initTextWidgets()
{
    moneyText = makeWidget<TextWidget>("123456", 60, 255, 255, 255, this);
    moneyText->setLocalPosition(w - 230, 65);

    int smallWindowXSize = 350;
    int smallWindowYSize = 350;
    int curX = 100;
    int curY = -smallWindowYSize + 200;
    for(int i = 0; i < sellItemNum; ++i)
    {
        if(i%2 == 0)
        {
            curX = 100;
            curY += smallWindowYSize + 100;
        }
        else
        {
            curX = RTWidth - 100 - smallWindowYSize;
        }
        crystalNumTexts.emplace_back(makeWidget<TextWidget>(crystalNums[i], 50, 255, 255, 255, this));
        crystalNumTexts[i]->setLocalPosition(curX + 20, curY + 10);

        priceTexts.emplace_back(makeWidget<TextWidget>(prices[i], 45, 255, 255, 255, this));
        auto textScale = priceTexts[i]->getScale();
        auto buttonScale = buyButtons[i]->getScale();
        auto textXPos = buttonScale.first - textScale.first;
        auto textYPos = crystals[i]->getLocalPosition().second + crystals[i]->getScale().second +
                (buttonScale.second - textScale.second) / 2;
        priceTexts[i]->setLocalPosition(curX + smallWindowXSize / 2 - 90 + textXPos / 2, textYPos);
    }
}
