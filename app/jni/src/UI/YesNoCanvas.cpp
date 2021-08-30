#include "YesNoCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "../GlobalFunction.h"
#include "../AirplaneController.h"
#include <string>

using namespace GlobalFunction;

YesNoCanvas::YesNoCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY):
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    initCanvas();
}

YesNoCanvas::~YesNoCanvas()
{

}

void YesNoCanvas::initCanvas()
{
    window = new ImageWidget("image/UIImage/smallWindow.png");
    window->setScale(w, h);
    window->setLocalPosition(0, 0);
    addWidgetToBuffer(window);

    yesButton = new ButtonWidget("image/UIImage/downButton.png","image/UIImage/upButton.png");
    yesButton->setScale(150, 100);
    yesButton->setLocalPosition(100, h - 200);
    yesButton->buttonUpEvent = [this]()
    {
        auto PC = Cast<AirplaneController>(GetPlayerController());
        PC->processingBuyProtocol();
        removeFromViewport();
    };
    addWidgetToBuffer(yesButton);
    addButtonToBuffer(yesButton);

    noButton = new ButtonWidget("image/UIImage/downButton.png","image/UIImage/upButton.png");
    noButton->setScale(150, 100);
    noButton->setLocalPosition(w - 150 - 100, h - 200);
    noButton->buttonUpEvent = [this]()
    {
        removeFromViewport();
    };
    addWidgetToBuffer(noButton);
    addButtonToBuffer(noButton);

    askText = new TextWidget("Are you sure?", 60, 255, 255, 255);
    askText->setLocalPosition((w - askText->getScale().first) / 2, 50);
    addWidgetToBuffer(askText);

    yesText = new TextWidget("Yes", 50, 255, 255, 255);
    int textYPos = (h - 200) + (yesButton->getScale().second - yesText->getScale().second) / 2;
    yesText->setLocalPosition(100 + (yesButton->getScale().first - yesText->getScale().first) / 2 , textYPos);
    addWidgetToBuffer(yesText);

    noText = new TextWidget("N o", 50, 255, 255, 255);
    noText->setLocalPosition(w - 150 - 100 + (noButton->getScale().first - noText->getScale().first) / 2, textYPos);
    addWidgetToBuffer(noText);
}

void YesNoCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender();
    }
}

void YesNoCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

bool YesNoCanvas::handleEvent(SDL_Event& e)
{
    return Canvas::handleEvent(e);
}

void YesNoCanvas::update(float deltaTime)
{
    if(visibility)
    {
        Canvas::update(deltaTime);
    }
}
