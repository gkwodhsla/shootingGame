#include "LoginCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "EditBoxWidget.h"
#include "TitleController.h"
#include "../GlobalFunction.h"
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
    initButton();
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

void LoginCanvas::initButton() {
    signInButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    signInButton->setScale(500, 100);
    signInButton->setLocalPosition((w - signInButton->getScale().first) / 2, 1200);
    addWidgetToBuffer(signInButton);
    addButtonToBuffer(signInButton);

    loginButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    loginButton->setScale(500, 100);
    loginButton->setLocalPosition((w - signInButton->getScale().first) / 2, 1500);
    loginButton->buttonUpEvent = []()
    {
        auto PC = GlobalFunction::Cast<TitleController>(GlobalFunction::GetPlayerController());
        if(PC)
        {
            PC->goToMainLevel();
        }
    };
    addWidgetToBuffer(loginButton);
    addButtonToBuffer(loginButton);

    auto signButtonLoc = signInButton->getLocalPosition();
    auto signButtonSize = signInButton->getScale();
    signInText = new TextWidget("Sign in", 50, 255, 255, 255);
    auto signTextSize = signInText->getScale();
    signInText->setLocalPosition(signButtonLoc.first + (signButtonSize.first - signTextSize.first) / 2,
                                 signButtonLoc.second + (signButtonSize.second - signTextSize.second) / 2);
    addWidgetToBuffer(signInText);

    auto loginButtonLoc = loginButton->getLocalPosition();
    auto loginButtonSize = loginButton->getScale();
    loginText = new TextWidget("Sign up", 50, 255, 255, 255);
    auto loginTextSize = loginText->getScale();
    loginText->setLocalPosition(loginButtonLoc.first + (loginButtonSize.first - loginTextSize.first) / 2,
                                loginButtonLoc.second + (loginButtonSize.second - loginTextSize.second) / 2);
    addWidgetToBuffer(loginText);
}