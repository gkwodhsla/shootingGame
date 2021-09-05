#include "YesNoCanvas.h"
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
    window = makeWidget<ImageWidget>("image/UIImage/smallWindow.png");
    window->setScale(RTWidth, RTHeight);
    window->setLocalPosition(0, 0);

    yesButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png","image/UIImage/upButton.png",
                                 "", "sound/purchase.wav");
    yesButton->setScale(150 * canvasXRatio, 100 * canvasYRatio);
    yesButton->setLocalPosition(100, RTHeight - yesButton->getScale().second - 100);
    yesButton->buttonUpEvent = [this]()
    {
        auto PC = Cast<AirplaneController>(GetPlayerController());
        PC->processingBuyProtocol();
        removeFromViewport();
    };

    noButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png","image/UIImage/upButton.png",
                                "", "sound/click.wav");
    noButton->setScale(150 * canvasXRatio, 100 * canvasYRatio);
    noButton->setLocalPosition(RTWidth - noButton->getScale().first - 100, RTHeight - noButton->getScale().second - 100);
    noButton->buttonUpEvent = [this]()
    {
        removeFromViewport();
    };

    askText = makeWidget<TextWidget>("Are you sure?", 100, 255, 255, 255);
    askText->setScale(askText->getScale().first*canvasXRatio,
                      askText->getScale().second*canvasYRatio);
    askText->setLocalPosition((RTWidth - askText->getScale().first) / 2, 50);

    yesText = makeWidget<TextWidget>("Yes", 60, 255, 255, 255);
    yesText->setScale(yesText->getScale().first * canvasXRatio, yesText->getScale().second * canvasYRatio);
    int textYPos = (RTHeight - noButton->getScale().second - 100) + (yesButton->getScale().second - yesText->getScale().second) / 2;
    yesText->setLocalPosition(100 + (yesButton->getScale().first - yesText->getScale().first) / 2 , textYPos);

    noText = makeWidget<TextWidget>("N o", 60, 255, 255, 255);
    noText->setScale(noText->getScale().first * canvasXRatio, noText->getScale().second * canvasYRatio);
    noText->setLocalPosition(RTWidth - noButton->getScale().first - 100 + (noButton->getScale().first - noText->getScale().first) / 2, textYPos);
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
