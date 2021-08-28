#include "ShopCanvas.h"
#include "TextWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../HPlayerController.h"
#include "../Actors/Airplane.h"
#include "../GlobalFunction.h"
#include <android/log.h>

using namespace GlobalFunction;

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

bool ShopCanvas::handleEvent(SDL_Event &e)
{
    return Canvas::handleEvent(e);
}

void ShopCanvas::update(float deltaTime)
{
    Canvas::update(deltaTime);
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
    attackUpgradeButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Add Player Attack Power +10");
        this->explanationText2->changeText(" ");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(attackUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::ATTACK;
    };

    //곧 이벤트를 추가하자
    attackPowerText = new TextWidget(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower),
                                     50, 255, 255, 255);
    attackPowerText->setLocalPosition(150, 440);
    addWidgetToBuffer(attackPowerText);


    bulletUpgradeButton = new ButtonWidget("image/UIImage/bulletDownButton.png", "image/UIImage/bulletUpButton.png");
    bulletUpgradeButton->setScale(180, 180);
    bulletUpgradeButton->setLocalPosition(450, 250);
    addWidgetToBuffer(bulletUpgradeButton);
    addButtonToBuffer(bulletUpgradeButton);
    bulletUpgradeButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Add Player Bullet +1 when you finished");
        this->explanationText2->changeText("your upgrade to maximum");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(bulletUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::BULLET;
    };
    //
    bulletText = new TextWidget(std::to_string(curBullet) + "/" + std::to_string(maxBullet),
                               50, 255, 255, 255);
    bulletText->setLocalPosition(520, 440);
    addWidgetToBuffer(bulletText);

    airplaneUpgradeButton = new ButtonWidget("image/UIImage/fighterDownButton.png", "image/UIImage/fighterUpButton.png");
    airplaneUpgradeButton->setScale(180, 180);
    airplaneUpgradeButton->setLocalPosition(w - 270, 250);
    addWidgetToBuffer(airplaneUpgradeButton);
    addButtonToBuffer(airplaneUpgradeButton);
    airplaneUpgradeButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Upgrade fighter and unlock new upgrade");
        this->explanationText2->changeText("before upgrading you must upgrade");
        this->explanationText3->changeText("attack power and bullet to maximum");
        this->explanationText4->changeText("Cost: " + std::to_string(airplaneUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::AIRPLANE;
    };
    //

    airplaneText = new TextWidget(std::to_string(curAirplane) + "/" + std::to_string(maxAirplane),
                                  50, 255, 255, 255);
    airplaneText->setLocalPosition(w - 200, 440);
    addWidgetToBuffer(airplaneText);

    missileButton = new ButtonWidget("image/UIImage/missileDownButton.png", "image/UIImage/missileUpButton.png");
    missileButton->setScale(180, 180);
    missileButton->setLocalPosition(80 + 180, 500);
    addWidgetToBuffer(missileButton);
    addButtonToBuffer(missileButton);
    missileButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Get this special skill");
        this->explanationText2->changeText("your enemy will be fatally wounded");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(missileFee));
        whichItemButton = WHICH_ITEM_BUTTON::MISSILE;
    };
    //
    missileText = new TextWidget(std::to_string(curMissile) + "/" + std::to_string(maxMissile),
                                     50, 255, 255, 255);
    missileText->setLocalPosition(80 + 180 + 60, 690);
    addWidgetToBuffer(missileText);

    shieldButton = new ButtonWidget("image/UIImage/shieldDownButton.png", "image/UIImage/shieldUpButton.png");
    shieldButton->setScale(180, 180);
    shieldButton->setLocalPosition(450 + 180, 500);
    addWidgetToBuffer(shieldButton);
    addButtonToBuffer(shieldButton);
    shieldButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("This shield prevents enemy attacks");
        this->explanationText2->changeText("for three seconds");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(shieldFee));
        whichItemButton = WHICH_ITEM_BUTTON::SHIELD;
    };
    //
    shieldText = new TextWidget(std::to_string(curShield) + "/" + std::to_string(maxShield),
                                50, 255, 255, 255);
    shieldText->setLocalPosition(450 + 180 + 60, 690);
    addWidgetToBuffer(shieldText);

    explanationWindow = new ImageWidget("image/UIImage/box.png");
    explanationWindow->setScale(w - 100, 350);
    explanationWindow->setLocalPosition(50, 800);
    addWidgetToBuffer(explanationWindow);

    explanationText1 = new TextWidget(" ", 50, 255, 255, 255);
    explanationText1->setLocalPosition(150, 850);
    addWidgetToBuffer(explanationText1);

    explanationText2 = new TextWidget(" ", 50, 255, 255, 255);
    explanationText2->setLocalPosition(150, 900);
    addWidgetToBuffer(explanationText2);

    explanationText3 = new TextWidget(" ", 50, 255, 255, 255);
    explanationText3->setLocalPosition(150, 950);
    addWidgetToBuffer(explanationText3);

    explanationText4 = new TextWidget(" ", 50, 255, 255, 255);
    explanationText4->setLocalPosition(150, 1000);
    addWidgetToBuffer(explanationText4);

    buyButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    buyButton->setScale(200, 150);
    buyButton->setLocalPosition(w / 2 - 100, 1150);
    addWidgetToBuffer(buyButton);
    addButtonToBuffer(buyButton);
    buyButton->buttonUpEvent = [this]()mutable
    {
        switch (whichItemButton)
        {
            case WHICH_ITEM_BUTTON::ATTACK:
                if(curCrystal >= attackUpgradeFee && curAttackPower < maxAttackPower)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    int curPlayerAttackPower = airplane->getPlayerAttackPower();
                    curPlayerAttackPower += 10;
                    airplane->setPlayerAttackPower(curPlayerAttackPower);
                    curCrystal -= attackUpgradeFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    attackUpgradeFee += attackUpgradeGap;
                    ++curAttackPower;
                    attackPowerText->changeText(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower));
                    explanationText4->changeText("Cost: " + std::to_string(attackUpgradeFee));
                    attackUpgradeGap += 10;
                }
                break;
            case WHICH_ITEM_BUTTON::BULLET:
                if(curCrystal >= bulletUpgradeFee && curBullet < maxBullet)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    curCrystal -= bulletUpgradeFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    bulletUpgradeFee += bulletUpgradeGap;
                    ++curBullet;
                    bulletText->changeText(std::to_string(curBullet) + "/" + std::to_string(maxBullet));
                    explanationText4->changeText("Cost: " + std::to_string(bulletUpgradeFee));
                    bulletUpgradeGap += 10;
                    if(curBullet == maxBullet)
                    {
                        int curBulletNum = airplane->getPlayerBulletCnt();
                        airplane->setPlayerBulletCnt(curBulletNum + 1);
                    }
                }
                break;
            case WHICH_ITEM_BUTTON::AIRPLANE:
                if(curCrystal >= airplaneUpgradeFee && curAirplane < maxAirplane &&
                curAttackPower == maxAttackPower && curBullet == maxBullet)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    curCrystal -= airplaneUpgradeFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    airplaneUpgradeFee += 5000;
                    ++curAirplane;
                    airplaneText->changeText(std::to_string(curAirplane) + "/" + std::to_string(maxAirplane));
                    explanationText4->changeText("Cost: " + std::to_string(airplaneUpgradeFee));
                    PLAYER_AIRPLANE_SHAPE curShape = airplane->getPlayerAirplaneShape();
                    if(curShape == PLAYER_AIRPLANE_SHAPE::SHAPE1)
                    {
                        airplane->setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE::SHAPE2);
                    }
                    else if(curShape == PLAYER_AIRPLANE_SHAPE::SHAPE2)
                    {
                        airplane->setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE::SHAPE3);
                    }
                    curAttackPower = 0;
                    curBullet = 0;
                    attackPowerText->changeText(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower));
                    bulletText->changeText(std::to_string(curBullet) + "/" + std::to_string(maxBullet));
                }
                break;
            case WHICH_ITEM_BUTTON::MISSILE:
                if(curCrystal >= missileFee && curMissile < maxMissile)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    curCrystal -= missileFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    ++curMissile;
                    missileText->changeText(std::to_string(curMissile) + "/" + std::to_string(maxMissile));
                    int curMissileNum = airplane->getMissileCnt();
                    airplane->setMissileCnt(curMissileNum + 1);
                }
                break;
            case WHICH_ITEM_BUTTON::SHIELD:
                if(curCrystal >= shieldFee && curShield < maxShield)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    curCrystal -= shieldFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    ++curShield;
                    shieldText->changeText(std::to_string(curShield) + "/" + std::to_string(maxShield));
                    int curShieldNum = airplane->getShieldCnt();
                    airplane->setShieldCnt(curShieldNum + 1);
                }
                break;
        }
    };

    buyText = new TextWidget("BUY", 55, 255, 255, 255);
    buyText->setLocalPosition(w / 2 - 40, 1200);
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