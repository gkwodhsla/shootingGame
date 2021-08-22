#pragma once
#include "Canvas.h"

class TextWidget;
class ButtonWidget;
class ImageWidget;

class ShopCanvas : public Canvas
{
public:
    ShopCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~ShopCanvas();
    virtual void canvasRender();
    virtual void render();
    virtual void handleEvent(SDL_Event& e);

public:
    bool getIsPlayButtonClicked();
    void setIsPlayButtonClicked(bool isClicked);
    void incMaxStage();
    int getCurStage();
    int getMaxStage();

private:
    void initWidgets();

private:
    ImageWidget* bgImage = nullptr;
    ImageWidget* shopTitleImage = nullptr;
    ImageWidget* crystalImage = nullptr;
    ImageWidget* moneyWindowImage = nullptr;
    TextWidget* moneyText = nullptr;
    ButtonWidget* attackUpgradeButton = nullptr;
    ButtonWidget* bulletUpgradeButton = nullptr;
    ButtonWidget* airplaneUpgradeButton = nullptr;
    ButtonWidget* missileButton = nullptr;
    ButtonWidget* shieldButton = nullptr;
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
    int curStage = 1;
    int maxStage = 100;
    int minStage = 1;
    int curCrystal = 1234;
    bool isPlayButtonClicked = false;
};