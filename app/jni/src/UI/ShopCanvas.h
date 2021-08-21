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
    ButtonWidget* playButton = nullptr;
    ButtonWidget* decButton = nullptr;
    ButtonWidget* incButton = nullptr;
    TextWidget* stageText = nullptr;
    ImageWidget* bgImage = nullptr;
    int curStage = 1;
    int maxStage = 100;
    int minStage = 1;
    bool isPlayButtonClicked = false;
};