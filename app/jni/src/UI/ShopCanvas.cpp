#include "ShopCanvas.h"
#include "TextWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "../Framework.h"
#include <android/log.h>

ShopCanvas::ShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    initWidgets();
}

ShopCanvas::~ShopCanvas()
{

}

void ShopCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender(); // 여기서 렌더타켓을 초기화 시켜준다.
    }
}

void ShopCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

void ShopCanvas::handleEvent(SDL_Event &e)
{
    Canvas::handleEvent(e);
    //위젯을 순회하며 발생한 이벤트가 있는지 검사하고 적절한 함수를 호출해준다.
}

bool ShopCanvas::getIsPlayButtonClicked()
{
    return isPlayButtonClicked;
}

void ShopCanvas::setIsPlayButtonClicked(bool isClicked)
{
    isPlayButtonClicked = isClicked;
}

void ShopCanvas::incMaxStage()
{
    ++maxStage;
}

int ShopCanvas::getCurStage()
{
    return curStage;
}

int ShopCanvas::getMaxStage()
{
    return maxStage;
}


void ShopCanvas::initWidgets()
{
    bgImage = new ImageWidget("image/UIImage/window.png");
    bgImage->setLocalPosition(0, 0);
    bgImage->setScale(w, h);
    addWidgetToBuffer(bgImage);

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

    moneyText = new TextWidget(std::to_string(curCrystal), 60, 255, 255, 255);
    moneyText->setLocalPosition(w - 200, 65);
    addWidgetToBuffer(moneyText);

    attackUpgradeButton = new ButtonWidget("image/UIImage/attackDownButton.png", "image/UIImage/attackUpButton.png");
    attackUpgradeButton->setScale(180, 180);
    attackUpgradeButton->setLocalPosition(80, 250);
    addWidgetToBuffer(attackUpgradeButton);
    addButtonToBuffer(attackUpgradeButton);
    //곧 이벤트를 추가하자

    bulletUpgradeButton = new ButtonWidget("image/UIImage/bulletDownButton.png", "image/UIImage/bulletUpButton.png");
    bulletUpgradeButton->setScale(180, 180);
    bulletUpgradeButton->setLocalPosition(450, 250);
    addWidgetToBuffer(bulletUpgradeButton);
    addButtonToBuffer(bulletUpgradeButton);

    airplaneUpgradeButton = new ButtonWidget("image/UIImage/fighterDownButton.png", "image/UIImage/fighterUpButton.png");
    airplaneUpgradeButton->setScale(180, 180);
    airplaneUpgradeButton->setLocalPosition(w - 270, 250);
    addWidgetToBuffer(airplaneUpgradeButton);
    addButtonToBuffer(airplaneUpgradeButton);

    missileButton = new ButtonWidget("image/UIImage/missileDownButton.png", "image/UIImage/missileUpButton.png");
    missileButton->setScale(180, 180);
    missileButton->setLocalPosition(80 + 180, 500);
    addWidgetToBuffer(missileButton);
    addButtonToBuffer(missileButton);

    shieldButton = new ButtonWidget("image/UIImage/shieldDownButton.png", "image/UIImage/shieldUpButton.png");
    shieldButton->setScale(180, 180);
    shieldButton->setLocalPosition(450 + 180, 500);
    addWidgetToBuffer(shieldButton);
    addButtonToBuffer(shieldButton);

    explanationWindow = new ImageWidget("image/UIImage/box.png");
    explanationWindow->setScale(w - 100, 350);
    explanationWindow->setLocalPosition(50, 750);
    addWidgetToBuffer(explanationWindow);

    explanationText1 = new TextWidget("explanation line first", 55, 255, 255, 255);
    explanationText1->setLocalPosition(180, 800);
    addWidgetToBuffer(explanationText1);

    explanationText2 = new TextWidget("explanation line second", 55, 255, 255, 255);
    explanationText2->setLocalPosition(180, 850);
    addWidgetToBuffer(explanationText2);

    explanationText3 = new TextWidget("explanation line third", 55, 255, 255, 255);
    explanationText3->setLocalPosition(180, 900);
    addWidgetToBuffer(explanationText3);

    explanationText4 = new TextWidget("explanation line fourth", 55, 255, 255, 255);
    explanationText4->setLocalPosition(180, 950);
    addWidgetToBuffer(explanationText4);

    buyButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    buyButton->setScale(200, 150);
    buyButton->setLocalPosition(w / 2 - 100, 1100);
    addWidgetToBuffer(buyButton);
    addButtonToBuffer(buyButton);

    buyText = new TextWidget("BUY", 55, 255, 255, 255);
    buyText->setLocalPosition(w / 2 - 40, 1150);
    addWidgetToBuffer(buyText);

    playButton = new ButtonWidget("image/UIImage/playDownButton.png", "image/UIImage/playUpButton.png");
    playButton->buttonUpEvent = [this]()mutable
            {
                isPlayButtonClicked = true;
            };
    playButton->setLocalPosition(w - 250, h - 300);
    addWidgetToBuffer(playButton);
    addButtonToBuffer(playButton);

    incButton = new ButtonWidget("image/UIImage/rightDownButton.png", "image/UIImage/rightUpButton.png");
    incButton->buttonUpEvent = [this]()mutable
            {
                if(curStage < maxStage)
                {
                    ++curStage;
                    std::string temp = "Stage: ";
                    temp += std::to_string(curStage);
                    stageText->changeText(temp);
                }
            };
    incButton->setLocalPosition(570, h - 300);
    addWidgetToBuffer(incButton);
    addButtonToBuffer(incButton);

    decButton = new ButtonWidget("image/UIImage/leftDownButton.png", "image/UIImage/leftUpButton.png");
    decButton->buttonUpEvent = [this]()mutable
            {
                if(curStage > minStage)
                {
                    --curStage;
                    std::string temp = "Stage: ";
                    temp += std::to_string(curStage);
                    stageText->changeText(temp);
                }
            };
    decButton->setLocalPosition(50, h - 300);
    addWidgetToBuffer(decButton);
    addButtonToBuffer(decButton);

    stageText = new TextWidget("Stage: 1", 90, 255, 255, 255);
    stageText->setLocalPosition(265, h - 250);
    addWidgetToBuffer(stageText);

}
