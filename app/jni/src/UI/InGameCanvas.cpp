#include "InGameCanvas.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "../GlobalFunction.h"
#include "../Actors/Airplane.h"
#include <android/log.h>
#include <string>

using namespace GlobalFunction;

InGameCanvas::InGameCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    changeWindowAlphaValue(255);
    player = Cast<Airplane>(GetPlayerPawn());
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

void InGameCanvas::update(float deltaTime)
{
    Canvas::update(deltaTime);
    thunderCountText->changeText(std::to_string(player->getMissileCnt()));
    shieldCountText->changeText(std::to_string(player->getShieldCnt()));
}

void InGameCanvas::initWidgets()
{
    thunderButton = new ButtonWidget("image/UIImage/thunderSkillButton.png", "image/UIImage/thunderSkillButton.png", "", "");
    thunderButton->setScale(150, 150);
    thunderButton->setLocalPosition(50, h - 200);
    auto thunderDownEvent = [=]() mutable
    {
        if(player)
        {
            player->enableThunder();
        }
    };
    thunderButton->registerbuttonDownEvent(thunderDownEvent);
    addWidgetToBuffer(thunderButton);
    addButtonToBuffer(thunderButton);

    shieldButton = new ButtonWidget("image/UIImage/shieldSkillButton.png", "image/UIImage/shieldSkillButton.png", "", "");
    shieldButton->setScale(150, 150);
    shieldButton->setLocalPosition(50, h - 500);
    auto shieldDownEvent = [=]() mutable
    {
        if(player)
        {
            player->enableShield();
        }
    };
    shieldButton->registerbuttonDownEvent(shieldDownEvent);
    addWidgetToBuffer(shieldButton);
    addButtonToBuffer(shieldButton);


    shieldCountText = new TextWidget(std::to_string(player->getShieldCnt()),40, 255, 255, 255);
    shieldCountText->setLocalPosition(50 + 65, h - 350);
    addWidgetToBuffer(shieldCountText);

    thunderCountText = new TextWidget(std::to_string(player->getMissileCnt()), 40, 255, 255, 255);
    thunderCountText->setLocalPosition(50 + 65, h - 50);
    addWidgetToBuffer(thunderCountText);

}
