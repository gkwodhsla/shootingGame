#include "LoginCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "EditBoxWidget.h"
#include <string>

LoginCanvas::LoginCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    backgroundImg = new ImageWidget("image/background/login.png");
    backgroundImg->setScale(canvasW, canvasH);
    backgroundImg->setLocalPosition(0, 0);
    addWidgetToBuffer(backgroundImg);

    gameNameText = new TextWidget("Shooting Game", 120, 255, 255, 255);
    gameNameText->setLocalPosition((canvasW - gameNameText->getScale().first) / 2, 300);
    addWidgetToBuffer(gameNameText);

    initEditBox();
}

LoginCanvas::~LoginCanvas()
{

}

void LoginCanvas::canvasRender()
{
    if(visibility)
    {
        Canvas::canvasRender();
    }
}

void LoginCanvas::render()
{
    if(visibility)
    {
        Canvas::render();
    }
}

bool LoginCanvas::handleEvent(SDL_Event &e)
{
    return Canvas::handleEvent(e);
}

void LoginCanvas::update(float deltaTime)
{
    Canvas::update(deltaTime);
}

void LoginCanvas::initEditBox()
{
    emailBox = new EditBoxWidget("image/UIImage/box.png", "image/UIImage/caret.png", "e-mail",40, 255, 255, 255);
    emailBox->setScale(500, 100);
    emailBox->setLocalPosition((w - emailBox->getScale().first) / 2, 600);
    addWidgetToBuffer(emailBox);
    addEditBoxToBuffer(emailBox);

    passwordBox = new EditBoxWidget("image/UIImage/box.png", "image/UIImage/caret.png", "password",40, 255, 255, 255);
    passwordBox->setScale(500, 100);
    passwordBox->setLocalPosition((w - passwordBox->getScale().first) / 2, 900);
    addWidgetToBuffer(passwordBox);
    addEditBoxToBuffer(passwordBox);

}