#include "LoginCanvas.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "EditBoxWidget.h"
#include "TitleController.h"
#include "../GlobalFunction.h"
#include "../DBManager.h"
#include <string>
#include <android/log.h>

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
    if(isCheckingSignIn)
    {
        if (result.status() == firebase::kFutureStatusComplete)
        {
            if (result.error() == firebase::auth::kAuthErrorNone) // 새로운 유저가 생성되면 유저가 생성됐다고 알려주고 DB에 하나 만들어준다.
            {
                firebase::auth::User* user = *result.result();
                Framework::UID = user->uid();
                signInResultText->changeText("Sign in success");
                Framework::dbManager->createDBForNewUser();
            }
            else
            {
                signInResultText->changeText(result.error_message());
            }
            isShowSignInText = true;
            msgShowTime = maxMsgShowTime;
            signInResultText->setVisibility(true);
            signInResultText->setLocalPosition((w - signInResultText->getScale().first) / 2,800);
            isCheckingSignIn = false;
        }
    }
    else if(isCheckingSignUp)
    {
        if (result.status() == firebase::kFutureStatusComplete)
        {
            if (result.error() == firebase::auth::kAuthErrorNone)
            {
                firebase::auth::User* user = *result.result();
                signInResultText->changeText("Log In Success");
                Framework::UID = user->uid();
                readDBResult = Framework::dbManager->getDBRef().Child("users").Child(Framework::UID).GetValue();
                isCheckingReadDataFromDB = true;
                /*auto PC = GlobalFunction::Cast<TitleController>(GlobalFunction::GetPlayerController());
                if(PC)
                {
                    PC->goToMainLevel();
                }*/
            }
            else
            {
                signInResultText->changeText(result.error_message());
            }
            isShowSignInText = true;
            msgShowTime = maxMsgShowTime;
            signInResultText->setVisibility(true);
            signInResultText->setLocalPosition((w - signInResultText->getScale().first) / 2,800);
            isCheckingSignUp = false;
        }
    }
    else if(isCheckingEmailSend)
    {
        if (result2.status() == firebase::kFutureStatusComplete)
        {
            if (result2.error() == firebase::auth::kAuthErrorNone)
            {
                signInResultText->changeText("Email send success");
            }
            else
            {
                signInResultText->changeText(result2.error_message());
            }
            isShowSignInText = true;
            msgShowTime = maxMsgShowTime;
            signInResultText->setVisibility(true);
            signInResultText->setLocalPosition((w - signInResultText->getScale().first) / 2,800);
            isCheckingEmailSend = false;
        }
    }
    else if(isCheckingReadDataFromDB)
    {
        if (readDBResult.status() != firebase::kFutureStatusPending)
        {
            if (readDBResult.status() != firebase::kFutureStatusComplete)
            {
                //LogMessage("ERROR: GetValue() returned an invalid result.");
                // Handle the error...
            }
            else if (readDBResult.error() != firebase::database::kErrorNone)
            {

            }
            else
            {
                auto PC = GlobalFunction::Cast<TitleController>(GlobalFunction::GetPlayerController());
                if(PC)
                {
                    Framework::dbManager->readFromDB(readDBResult.result());
                    PC->goToMainLevel();
                    isCheckingReadDataFromDB = false;
                }
            }
        }
    }
    if(isShowSignInText)
    {
        msgShowTime -= deltaTime;
        if(msgShowTime <= 0.0f)
        {
            isShowSignInText = false;
            signInResultText->setVisibility(false);
        }
    }
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
    signInButton->buttonUpEvent = [this]() mutable
    {
        std::string emailStr = emailBox->getContent();
        std::string passwordStr = passwordBox->getContent();
        Framework::auth->CreateUserWithEmailAndPassword(emailStr.c_str(), passwordStr.c_str());
        isCheckingSignIn = true;
        result = Framework::auth->CreateUserWithEmailAndPasswordLastResult();
    };
    addWidgetToBuffer(signInButton);
    addButtonToBuffer(signInButton);

    resetButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    resetButton->setScale(500, 100);
    resetButton->setLocalPosition((w - signInButton->getScale().first) / 2, 1400);
    resetButton->buttonUpEvent = [this]() mutable
    {
        Framework::auth->SendPasswordResetEmail(this->emailBox->getContent().c_str());
        result2 = Framework::auth->SendPasswordResetEmailLastResult();
        isCheckingEmailSend = true;
    };
    addWidgetToBuffer(resetButton);
    addButtonToBuffer(resetButton);

    loginButton = new ButtonWidget("image/UIImage/downButton.png", "image/UIImage/upButton.png");
    loginButton->setScale(500, 100);
    loginButton->setLocalPosition((w - signInButton->getScale().first) / 2, 1600);
    loginButton->buttonUpEvent = [this]() mutable
    {
        std::string emailStr = emailBox->getContent();
        std::string passwordStr = passwordBox->getContent();
        Framework::auth->SignInWithEmailAndPassword(emailStr.c_str(), passwordStr.c_str());
        result = Framework::auth->SignInWithEmailAndPasswordLastResult();
        isCheckingSignUp = true;
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

    auto resetButtonLoc = resetButton->getLocalPosition();
    auto resetButtonSize = resetButton->getScale();
    resetText = new TextWidget("Send Password Reset Email", 40, 255, 255, 255);
    auto resetTextSize = resetText->getScale();
    resetText->setLocalPosition(resetButtonLoc.first + (resetButtonSize.first - resetTextSize.first) / 2,
                                resetButtonLoc.second + (resetButtonSize.second - resetTextSize.second) / 2);
    addWidgetToBuffer(resetText);

    signInResultText = new TextWidget("Sign in success", 40, 255, 255, 255);
    signInResultText->setLocalPosition((w - signInResultText->getScale().first) / 2,h - 300);
    signInResultText->setVisibility(false);
    addWidgetToBuffer(signInResultText);
}