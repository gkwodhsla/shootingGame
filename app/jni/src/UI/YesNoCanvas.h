#pragma once

#include "Canvas.h"

class ImageWidget;
class TextWidget;
class ButtonWidget;

class YesNoCanvas: public Canvas
{
public:
    YesNoCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~YesNoCanvas();
    virtual void canvasRender() override;
    virtual void render() override;
    virtual bool handleEvent(const SDL_Event& e) override;
    virtual void update(const float deltaTime) override;
private:
    void initCanvas();

private:
    ImageWidget* window = nullptr;
    ButtonWidget* yesButton = nullptr;
    ButtonWidget* noButton = nullptr;
    TextWidget* askText = nullptr;
    TextWidget* yesText = nullptr;
    TextWidget* noText = nullptr;
};