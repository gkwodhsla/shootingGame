#include "ShopCanvas.h"
#include "TextWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../HPlayerController.h"
#include "../Actors/Airplane.h"
#include "../AirplaneController.h"
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

bool ShopCanvas::handleEvent(const SDL_Event &e)
{
    return Canvas::handleEvent(e);
}

void ShopCanvas::update(const float deltaTime)
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
    ++curStage;
    std::string temp = "Stage: ";
    temp += std::to_string(curStage);
    stageText->changeText(temp);
}

int ShopCanvas::getCurStage()
{
    return curStage;
}

int ShopCanvas::getMaxStage()
{
    return maxStage;
}

void ShopCanvas::setMaxStage(int stage)
{
    maxStage = stage;
}

void ShopCanvas::updateShopState()
{
    attackPowerText->changeText(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower));
    bulletText->changeText(std::to_string(curBullet) + "/" + std::to_string(maxBullet));
    airplaneText->changeText(std::to_string(curAirplane) + "/" + std::to_string(maxAirplane));
    missileText->changeText(std::to_string(curMissile) + "/" + std::to_string(maxMissile));
    shieldText->changeText(std::to_string(curShield) + "/" + std::to_string(maxShield));
    moneyText->changeText(std::to_string(curCrystal));
}

void ShopCanvas::setShieldCnt(int cnt)
{
    curShield = cnt;
    updateShopState();
}

void ShopCanvas::setMissileCnt(int cnt)
{
    curMissile = cnt;
    updateShopState();
}

void ShopCanvas::addCrystal(int howMany)
{
    curCrystal += howMany;
}

int ShopCanvas::getCrystal()
{
    return curCrystal;
}

void ShopCanvas::setCrystal(int crystal)
{
    curCrystal = crystal;
    moneyText->changeText(std::to_string(curCrystal));
    updateCrystalText();
}

int ShopCanvas::getAttackUpgrade()
{
    return curAttackPower;
}

void ShopCanvas::setAttackUpgrade(int attackUpgrade)
{
    curAttackPower = attackUpgrade;
    updateShopState();
}

int ShopCanvas::getBulletUpgrade()
{
    return curBullet;
}

void ShopCanvas::setBulletUpgrade(int bulletUpgrade)
{
    curBullet = bulletUpgrade;
    updateShopState();
}

int ShopCanvas::getAirplaneUpgrade()
{
    return curAirplane;
}

void ShopCanvas::setAirplaneUpgrade(int airplaneUpgrade)
{
    curAirplane = airplaneUpgrade;
    updateShopState();
}

void ShopCanvas::updateCrystalText()
{
    moneyText->changeText(std::to_string(curCrystal));
    auto moneyTextScale = moneyText->getScale();
    moneyText->setLocalPosition(RTWidth - 250 + (200 - moneyTextScale.first) / 2,
                                40 + (moneyWindowImage->getScale().second - moneyTextScale.second) / 2);
}


void ShopCanvas::initWidgets()
{
    bgImage = makeWidget<ImageWidget>("image/UIImage/window.png", this);
    bgImage->setLocalPosition(0, 0);
    bgImage->setScale(RTWidth, RTHeight, true);

    shopTitleImage = makeWidget<ImageWidget>("image/UIImage/Header.png", this);
    shopTitleImage->setLocalPosition(RTWidth / 2 - 150, 40);
    shopTitleImage->setScale(300, 120);

    crystalImage = makeWidget<ImageWidget>("image/UIImage/crystal.png", this);
    crystalImage->setLocalPosition(RTWidth - 340, 35);
    crystalImage->setScale(90, 110);

    moneyWindowImage = makeWidget<ImageWidget>("image/UIImage/box.png", this);
    moneyWindowImage->setLocalPosition(RTWidth - 250, 40);
    moneyWindowImage->setScale(200, 110);

    moneyText = makeWidget<TextWidget>(std::to_string(curCrystal), 60, 255, 255, 255, this);
    auto moneyTextScale = moneyText->getScale();
    moneyText->setLocalPosition(RTWidth - 250 + (200 - moneyTextScale.first) / 2,
                                40 + (moneyWindowImage->getScale().second - moneyTextScale.second) / 2);
    moneyText->setLocalPosition(RTWidth - 250 + (200 - moneyTextScale.first) / 2, 40 + (110 - moneyTextScale.second) / 2);

    attackUpgradeButton = makeWidget<ButtonWidget>("image/UIImage/attackDownButton.png", "image/UIImage/attackUpButton.png",
                                           "", "sound/click.wav", this);
    attackUpgradeButton->setScale(180, 180);
    attackUpgradeButton->setLocalPosition(80, 250);
    attackUpgradeButton->buttonUpEvent = [this]()mutable
    {
        attackUpgradeFee = (curAirplane - 1) * 300 + curAttackPower * 30;
        this->explanationText1->changeText("Add Player Attack Power +5");
        this->explanationText2->changeText(" ");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(attackUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::ATTACK;
    };

    attackPowerText = makeWidget<TextWidget>(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower),
                                     50, 255, 255, 255, this);
    attackPowerText->setScale(attackPowerText->getScale().first,
                              attackPowerText->getScale().second);
    attackPowerText->setLocalPosition(attackUpgradeButton->getLocalPosition().first +
                                              (attackUpgradeButton->getScale().first - attackPowerText->getScale().first) / 2,
                                      attackUpgradeButton->getLocalPosition().second+attackUpgradeButton->getScale().second);


    bulletUpgradeButton = makeWidget<ButtonWidget>("image/UIImage/bulletDownButton.png", "image/UIImage/bulletUpButton.png",
                                           "", "sound/click.wav", this);
    bulletUpgradeButton->setScale(180, 180);
    bulletUpgradeButton->setLocalPosition(450, 250);
    bulletUpgradeButton->buttonUpEvent = [this]()mutable
    {
        bulletUpgradeFee = (curAirplane - 1) * 300 + curBullet * 30;
        this->explanationText1->changeText("Add Player Bullet +1 when you finished");
        this->explanationText2->changeText("your upgrade to maximum");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(bulletUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::BULLET;
    };

    bulletText = makeWidget<TextWidget>(std::to_string(curBullet) + "/" + std::to_string(maxBullet),
                               50, 255, 255, 255, this);
    bulletText->setScale(bulletText->getScale().first,
                         bulletText->getScale().second);
    bulletText->setLocalPosition(bulletUpgradeButton->getLocalPosition().first +
                                      (bulletUpgradeButton->getScale().first - bulletText->getScale().first) / 2,
                                 bulletUpgradeButton->getLocalPosition().second+bulletUpgradeButton->getScale().second);

    airplaneUpgradeButton = makeWidget<ButtonWidget>("image/UIImage/fighterDownButton.png", "image/UIImage/fighterUpButton.png",
                                             "", "sound/click.wav", this);
    airplaneUpgradeButton->setScale(180, 180);
    airplaneUpgradeButton->setLocalPosition(RTWidth - 270, 250);
    airplaneUpgradeButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Upgrade fighter and unlock new upgrade");
        this->explanationText2->changeText("before upgrading you must upgrade");
        this->explanationText3->changeText("attack power and bullet to maximum");
        this->explanationText4->changeText("Cost: " + std::to_string(airplaneUpgradeFee));
        whichItemButton = WHICH_ITEM_BUTTON::AIRPLANE;
    };
    //

    airplaneText = makeWidget<TextWidget>(std::to_string(curAirplane) + "/" + std::to_string(maxAirplane),
                                  50, 255, 255, 255, this);
    airplaneText->setScale(airplaneText->getScale().first,
                           airplaneText->getScale().second);
    airplaneText->setLocalPosition(airplaneUpgradeButton->getLocalPosition().first +
                                 (airplaneUpgradeButton->getScale().first - airplaneText->getScale().first) / 2,
                                   airplaneUpgradeButton->getLocalPosition().second+airplaneUpgradeButton->getScale().second);

    missileButton = makeWidget<ButtonWidget>("image/UIImage/missileDownButton.png", "image/UIImage/missileUpButton.png",
                                     "", "sound/click.wav", this);
    missileButton->setScale(180, 180);
    missileButton->setLocalPosition(80 + 180, 500);
    missileButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("Get this special skill");
        this->explanationText2->changeText("your enemy will be fatally wounded");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(missileFee));
        whichItemButton = WHICH_ITEM_BUTTON::MISSILE;
    };

    missileText = makeWidget<TextWidget>(std::to_string(curMissile) + "/" + std::to_string(maxMissile),
                                     50, 255, 255, 255, this);
    missileText->setScale(missileText->getScale().first,
                          missileText->getScale().second);
    missileText->setLocalPosition(missileButton->getLocalPosition().first +
                                   (missileButton->getScale().first - missileText->getScale().first) / 2,
                                  missileButton->getLocalPosition().second+missileButton->getScale().second);

    shieldButton = makeWidget<ButtonWidget>("image/UIImage/shieldDownButton.png", "image/UIImage/shieldUpButton.png",
                                    "", "sound/click.wav", this);
    shieldButton->setScale(180, 180);
    shieldButton->setLocalPosition(450 + 180, 500);
    shieldButton->buttonUpEvent = [this]()mutable
    {
        this->explanationText1->changeText("This shield prevents enemy attacks");
        this->explanationText2->changeText("for three seconds");
        this->explanationText3->changeText(" ");
        this->explanationText4->changeText("Cost: " + std::to_string(shieldFee));
        whichItemButton = WHICH_ITEM_BUTTON::SHIELD;
    };
    //
    shieldText = makeWidget<TextWidget>(std::to_string(curShield) + "/" + std::to_string(maxShield),
                                50, 255, 255, 255, this);
    shieldText->setScale(shieldText->getScale().first,
                         shieldText->getScale().second);
    shieldText->setLocalPosition(shieldButton->getLocalPosition().first +
                                  (shieldButton->getScale().first - shieldText->getScale().first) / 2,
                                 shieldButton->getLocalPosition().second+shieldButton->getScale().second);

    explanationWindow = makeWidget<ImageWidget>("image/UIImage/box.png", this);
    explanationWindow->setScale((RTWidth - 100), 450);
    explanationWindow->setLocalPosition(50, 800);

    explanationText1 = makeWidget<TextWidget>(" ", 50, 255, 255, 255, this);
    explanationText1->setLocalPosition(150, 850);

    explanationText2 = makeWidget<TextWidget>(" ", 50, 255, 255, 255, this);
    explanationText2->setLocalPosition(150, 900);

    explanationText3 = makeWidget<TextWidget>(" ", 50, 255, 255, 255, this);
    explanationText3->setLocalPosition(150, 950);

    explanationText4 = makeWidget<TextWidget>(" ", 50, 255, 255, 255, this);
    explanationText4->setLocalPosition(150, 1000);

    buyButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                 "", "sound/purchase.wav", this);
    buyButton->setScale(200, 150);
    buyButton->setLocalPosition(RTWidth / 2 - 100,
                                explanationWindow->getLocalPosition().second+explanationWindow->getScale().second);
    buyButton->buttonUpEvent = [this]()mutable
    {
        bool buySuccess = false;
        switch (whichItemButton)
        {
            case WHICH_ITEM_BUTTON::ATTACK:
                if(curCrystal >= attackUpgradeFee && curAttackPower < maxAttackPower)
                {
                    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
                    HPlayerController *PC = GetPlayerController();
                    Airplane* airplane = Cast<Airplane>(GetPlayerPawn());
                    int curPlayerAttackPower = airplane->getPlayerAttackPower();
                    curPlayerAttackPower += 5;
                    airplane->setPlayerAttackPower(curPlayerAttackPower);
                    curCrystal -= attackUpgradeFee;
                    moneyText->changeText(std::to_string(curCrystal));
                    attackUpgradeFee = (curAirplane - 1) * 300 + curAttackPower * 30;
                    ++curAttackPower;
                    attackPowerText->changeText(std::to_string(curAttackPower) + "/" + std::to_string(maxAttackPower));
                    explanationText4->changeText("Cost: " + std::to_string(attackUpgradeFee));
                    buySuccess = true;
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
                    bulletUpgradeFee = (curAirplane - 1) * 300 + curBullet * 30;
                    ++curBullet;
                    bulletText->changeText(std::to_string(curBullet) + "/" + std::to_string(maxBullet));
                    explanationText4->changeText("Cost: " + std::to_string(bulletUpgradeFee));
                    if(curBullet == maxBullet)
                    {
                        int curBulletNum = airplane->getPlayerBulletCnt();
                        airplane->setPlayerBulletCnt(curBulletNum + 1);
                    }
                    buySuccess = true;
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
                    buySuccess = true;
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
                    int curMissileNum = airplane->getThunderCnt();
                    airplane->setThunderCnt(curMissileNum + 1);
                    buySuccess = true;
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
                    buySuccess = true;
                }
                break;
        }
        auto mainLevel = Cast<MainLevel>(GetLevel());
        if(mainLevel)
        {
            mainLevel->writeGameDataToDB();
        }
        if(buySuccess)
        {
            buyButton->setButtonVolume(128);
        }
        else
        {
            buyButton->setButtonVolume(0);
        }
    };

    buyText = makeWidget<TextWidget>("BUY", 55, 255, 255, 255, this);
    buyText->setScale(buyText->getScale().first,
                      buyText->getScale().second);
    buyText->setLocalPosition(buyButton->getLocalPosition().first +
                                 (buyButton->getScale().first - shieldText->getScale().first) / 2,
                                 buyButton->getLocalPosition().second +
                                         (buyButton->getScale().second - buyText->getScale().second)/2);

    playButton = makeWidget<ButtonWidget>("image/UIImage/playDownButton.png", "image/UIImage/playUpButton.png",
                                  "", "sound/click.wav", this);
    playButton->buttonUpEvent = [this]()mutable
            {
                isPlayButtonClicked = true;
            };
    playButton->setLocalPosition(RTWidth - 250, RTHeight - 300);

    incButton = makeWidget<ButtonWidget>("image/UIImage/rightDownButton.png", "image/UIImage/rightUpButton.png",
                                 "", "sound/click.wav", this);
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

    incButton->buttonHoldEvent = [this]()mutable
    {
        if(curStage < maxStage)
        {
            ++curStage;
            std::string temp = "Stage: ";
            temp += std::to_string(curStage);
            stageText->changeText(temp);
        }
    };
    incButton->setLocalPosition(570, RTHeight - 300);

    decButton = makeWidget<ButtonWidget>("image/UIImage/leftDownButton.png", "image/UIImage/leftUpButton.png",
                                 "", "sound/click.wav", this);
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
    decButton->buttonHoldEvent = [this]()mutable
    {
        if(curStage > minStage)
        {
            --curStage;
            std::string temp = "Stage: ";
            temp += std::to_string(curStage);
            stageText->changeText(temp);
        }
    };
    decButton->setLocalPosition(50, RTHeight - 300);

    stageText = makeWidget<TextWidget>("Stage: 1", 90, 255, 255, 255, this);
    stageText->setLocalPosition(265, RTHeight - 250);

    changeButton = makeWidget<ButtonWidget>("image/UIImage/changeDownButton.png","image/UIImage/changeUpButton.png",
                                    "", "sound/click.wav", this);
    changeButton->setScale(120, 120);
    changeButton->setLocalPosition(100, 35);
    changeButton->buttonUpEvent = []()
    {
        auto PC = Cast<AirplaneController>(GetPlayerController());
        PC->changeShop();
    };

    updateCrystalText();
}