#include "InGameCanvas.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include <android/log.h>
#include <string>

InGameCanvas::InGameCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    changeWindowAlphaValue(255);
    initWidgets();
}

InGameCanvas::~InGameCanvas()
{

}

void InGameCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender();
    }
}

void InGameCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

bool InGameCanvas::handleEvent(SDL_Event &e)
{
    return Canvas::handleEvent(e);
}

void InGameCanvas::initWidgets()
{
    thunderButton = new ButtonWidget("image/UIImage/thunderSkillButton.png", "image/UIImage/thunderSkillButton.png");
    thunderButton->setScale(150, 150);
    thunderButton->setLocalPosition(50, h - 300);
    auto thunderDownEvent = []() mutable
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "thunder Button Down");
    };
    thunderButton->registerbuttonDownEvent(thunderDownEvent);
    addWidgetToBuffer(thunderButton);
    addButtonToBuffer(thunderButton);

    shieldButton = new ButtonWidget("image/UIImage/shieldSkillButton.png", "image/UIImage/shieldSkillButton.png");
    shieldButton->setScale(150, 150);
    shieldButton->setLocalPosition(50, h - 500);
    auto shieldDownEvent = []() mutable
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "shield Button Down");
    };
    shieldButton->registerbuttonDownEvent(shieldDownEvent);
    addWidgetToBuffer(shieldButton);
    addButtonToBuffer(shieldButton);

}
