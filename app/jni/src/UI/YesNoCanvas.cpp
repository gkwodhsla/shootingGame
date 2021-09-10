#include "YesNoCanvas.h"
#include "../GlobalFunction.h"
#include "../AirplaneController.h"
#include "../Level/MainLevel.h"
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
    window = makeWidget<ImageWidget>("image/UIImage/smallWindow.png", this);
    window->setScale(RTWidth, RTHeight, true);
    window->setLocalPosition(0, 0);

    yesButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png","image/UIImage/upButton.png",
                                 "", "sound/purchase.wav", this);
    yesButton->setScale(420, 300);
    yesButton->setLocalPosition(50, RTHeight - yesButton->getScale().second - 100);
    yesButton->buttonUpEvent = [this]()
    {
        auto PC = Cast<AirplaneController>(GetPlayerController());
        PC->processingBuyProtocol();
        auto mainLevel = Cast<MainLevel>(GetLevel());
        if(mainLevel)
        {
            mainLevel->writeGameDataToDB();
        }
        removeFromViewport();
    };

    noButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png","image/UIImage/upButton.png",
                                "", "sound/click.wav", this);
    noButton->setScale(420, 300);
    noButton->setLocalPosition(RTWidth - noButton->getScale().first - 50, RTHeight - noButton->getScale().second - 100);
    noButton->buttonUpEvent = [this]()
    {
        removeFromViewport();
    };

    askText = makeWidget<TextWidget>("Are you sure?", 130, 255, 255, 255, this);
    askText->setLocalPosition((RTWidth - askText->getScale().first) / 2, 400);

    yesText = makeWidget<TextWidget>("Yes", 90, 255, 255, 255, this);
    int textYPos = (RTHeight - noButton->getScale().second - 100) + (yesButton->getScale().second - yesText->getScale().second) / 2;
    yesText->setLocalPosition(50 + (yesButton->getScale().first - yesText->getScale().first) / 2 , textYPos);

    noText = makeWidget<TextWidget>("N o", 90, 255, 255, 255, this);
    noText->setLocalPosition(RTWidth - noButton->getScale().first - 50 + (noButton->getScale().first - noText->getScale().first) / 2, textYPos);
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

bool YesNoCanvas::handleEvent(const SDL_Event& e)
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
