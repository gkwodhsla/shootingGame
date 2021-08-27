#pragma once
#include "Canvas.h"

class TextWidget;
class ButtonWidget;

class InGameCanvas :public Canvas
{
public:
    InGameCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~InGameCanvas();
    virtual void canvasRender() override;
    virtual void render() override;
    virtual bool handleEvent(SDL_Event& e) override;
    void initWidgets();

private:
    TextWidget* shieldCoolTimeText = nullptr;
    TextWidget* thunderCoolTimeText = nullptr;
    ButtonWidget* thunderButton = nullptr;
    ButtonWidget* shieldButton = nullptr;

    float thunderCoolTime = 3.0f;
    float shieldCoolTime = 3.0f;
    const float maxThunderCoolTime = 3.0f;
    const float maxShieldCoolTime = 3.0f;
};

