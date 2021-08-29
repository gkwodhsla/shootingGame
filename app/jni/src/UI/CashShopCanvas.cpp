#include "CashShopCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include <string>
#include <vector>
#include <array>

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

void CashShopCanvas::initWindowImageWidgets()
{
    bgImg = new ImageWidget("image/UIImage/window.png");
    bgImg->setLocalPosition(0, 0);
    bgImg->setScale(w, h);
    addWidgetToBuffer(bgImg);

    shopTitleImage = new ImageWidget("image/UIImage/Header.png");
    shopTitleImage->setLocalPosition(w / 2 - 140, 40);
    shopTitleImage->setScale(300, 120);
    addWidgetToBuffer(shopTitleImage);

    crystalImage = new ImageWidget("image/UIImage/crystal.png");
    crystalImage->setLocalPosition(w - 340, 35);
    crystalImage->setScale(90, 110);
    addWidgetToBuffer(crystalImage);

    moneyWindowImage = new ImageWidget("image/UIImage/box.png");
    moneyWindowImage->setLocalPosition(w - 250, 40);
    moneyWindowImage->setScale(200, 110);
    addWidgetToBuffer(moneyWindowImage);

    int smallWindowXSize = (w - 400) / 2;
    int smallWindowYSize = (h - 1000) / 2;
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
            curX = w - 100 - smallWindowYSize;
        }
        smallWindows.emplace_back(new ImageWidget("image/UIImage/smallWindow.png"));
        smallWindows[i]->setScale(smallWindowXSize, smallWindowYSize);
        smallWindows[i]->setLocalPosition(curX, curY);
        addWidgetToBuffer(smallWindows[i]);

        crystals.emplace_back(new ImageWidget("image/UIImage/crystal" + std::to_string(i+1) + ".png"));
        crystals[i]->setScale(150, 150);
        crystals[i]->setLocalPosition(curX + smallWindowXSize / 2 - 75, curY + smallWindowYSize / 2 - 100);
        addWidgetToBuffer(crystals[i]);
    }
}

void CashShopCanvas::initButtonWidgets()
{
    int smallWindowXSize = (w - 400) / 2;
    int smallWindowYSize = (h - 1000) / 2;
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
            curX = w - 100 - smallWindowYSize;
        }
        buyButtons.emplace_back(new ButtonWidget("image/UIImage/downButton.png","image/UIImage/upButton.png"));
        buyButtons[i]->setScale(180, 80);
        buyButtons[i]->setLocalPosition(curX + smallWindowXSize / 2 - 90, curY + smallWindowYSize / 2 + 70);
        addWidgetToBuffer(buyButtons[i]);
        addButtonToBuffer(buyButtons[i]);
    }
    changeButton = new ButtonWidget("image/UIImage/changeDownButton.png","image/UIImage/changeUpButton.png");
    changeButton->setScale(120, 120);
    changeButton->setLocalPosition(100, 35);
    addWidgetToBuffer(changeButton);
    addButtonToBuffer(changeButton);
}

void CashShopCanvas::initTextWidgets()
{
    moneyText = new TextWidget("123456", 60, 255, 255, 255);
    moneyText->setLocalPosition(w - 230, 65);
    addWidgetToBuffer(moneyText);

    int smallWindowXSize = (w - 400) / 2;
    int smallWindowYSize = (h - 1000) / 2;
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
            curX = w - 100 - smallWindowYSize;
        }
        crystalNumTexts.emplace_back(new TextWidget(crystalNums[i], 50, 255, 255, 255));
        crystalNumTexts[i]->setLocalPosition(curX + 20, curY + 10);
        addWidgetToBuffer(crystalNumTexts[i]);

        priceTexts.emplace_back(new TextWidget(prices[i], 45, 255, 255, 255));
        auto textScale = priceTexts[i]->getScale();
        auto buttonScale = buyButtons[i]->getScale();
        auto textXPos = buttonScale.first - textScale.first;
        priceTexts[i]->setLocalPosition(curX + smallWindowXSize / 2 - 90 + textXPos / 2, curY + smallWindowYSize / 2 + 88);
        addWidgetToBuffer(priceTexts[i]);
    }
}
