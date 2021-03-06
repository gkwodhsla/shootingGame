#pragma once
#include "Canvas.h"

class TextWidget;
class ButtonWidget;
class ImageWidget;

enum class WHICH_ITEM_BUTTON
{
    ATTACK,
    BULLET,
    AIRPLANE,
    THUNDER,
    SHIELD
};

class ShopCanvas : public Canvas
{
public:
    ShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    ShopCanvas() = delete;
    ShopCanvas(const ShopCanvas&) = delete;
    ShopCanvas& operator=(const ShopCanvas&) = delete;
    virtual ~ShopCanvas();
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(const SDL_Event& e);
    virtual void update(const float deltaTime);

public:
    bool getIsPlayButtonClicked();
    void setIsPlayButtonClicked(bool isClicked);
    void incMaxStage();
    int getCurStage();
    int getMaxStage();
    void setMaxStage(int stage);
    void updateShopState();
    void setShieldCnt(int cnt);
    void setThunderCnt(int cnt);
    void addCrystal(int howMany);
    int getCrystal();
    void setCrystal(int crystal);
    void updateCrystalText();
    int getAttackUpgrade();
    void setAttackUpgrade(int attackUpgrade);
    int getBulletUpgrade();
    void setBulletUpgrade(int bulletUpgrade);
    int getAirplaneUpgrade();
    void setAirplaneUpgrade(int airplaneUpgrade);

private:
    void initWidgets();

private:
    ImageWidget* bgImage = nullptr;
    ImageWidget* shopTitleImage = nullptr;
    ImageWidget* crystalImage = nullptr;
    ImageWidget* moneyWindowImage = nullptr;
    TextWidget* moneyText = nullptr;
    ButtonWidget* attackUpgradeButton = nullptr;
    TextWidget* attackPowerText = nullptr;
    ButtonWidget* bulletUpgradeButton = nullptr;
    TextWidget* bulletText = nullptr;
    ButtonWidget* airplaneUpgradeButton = nullptr;
    TextWidget* airplaneText = nullptr;
    ButtonWidget* thunderButton = nullptr;
    TextWidget* thunderText = nullptr;
    ButtonWidget* shieldButton = nullptr;
    TextWidget* shieldText = nullptr;
    ImageWidget* explanationWindow = nullptr;
    TextWidget* explanationText1 = nullptr;
    TextWidget* explanationText2 = nullptr;
    TextWidget* explanationText3 = nullptr;
    TextWidget* explanationText4 = nullptr;
    ButtonWidget* buyButton = nullptr;
    TextWidget* buyText = nullptr;
    ButtonWidget* playButton = nullptr;
    ButtonWidget* decButton = nullptr;
    ButtonWidget* incButton = nullptr;
    TextWidget* stageText = nullptr;
    ButtonWidget* changeButton = nullptr;
    int curStage = 1;
    int maxStage = 100;
    int minStage = 1;
    int curCrystal = 0;
    int curAttackPower = 1;
    int curBullet = 1;
    int curAirplane = 1;
    int curThunder = 0;
    int curShield = 0;
    int attackUpgradeFee = 50;
    int bulletUpgradeFee = 50;
    int airplaneUpgradeFee = 3000;
    int thunderFee = 1000;
    int shieldFee = 1000;
    WHICH_ITEM_BUTTON whichItemButton;
    const int maxAttackPower = 7;
    const int maxBullet = 7;
    const int maxAirplane = 3;
    const int maxThunder = 1;
    const int maxShield = 3;
    bool isPlayButtonClicked = false;
};