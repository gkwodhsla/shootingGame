#pragma once
#include "Canvas.h"

class TextWidget;
class ButtonWidget;
class Airplane;

class InGameCanvas :public Canvas
{
public:
    InGameCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    InGameCanvas() = delete;
    InGameCanvas(const InGameCanvas&) = delete;
    InGameCanvas& operator=(const InGameCanvas&) = delete;
    virtual ~InGameCanvas();
    virtual void canvasRender() override;
    virtual void render() override;
    virtual bool handleEvent(const SDL_Event& e) override;
    virtual void update(const float deltaTime) override;
    void initWidgets();

private:
    ButtonWidget* thunderButton = nullptr;
    ButtonWidget* shieldButton = nullptr;
    TextWidget* shieldCountText = nullptr;
    TextWidget* thunderCountText = nullptr;

    float thunderCoolTime = 3.0f;
    float shieldCoolTime = 3.0f;
    const float maxThunderCoolTime = 3.0f;
    const float maxShieldCoolTime = 3.0f;

    Airplane* player = nullptr;
};

