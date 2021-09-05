#include "LoginCanvas.h"
#include "TitleController.h"
#include "../GlobalFunction.h"
#include "../DBManager.h"
#include <string>
#include <android/log.h>

LoginCanvas::LoginCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    backgroundImg = makeWidget<ImageWidget>("image/background/login.png");
    backgroundImg->setScale(RTWidth, RTHeight);
    backgroundImg->setLocalPosition(0, 0);

    gameNameText = makeWidget<TextWidget>("Shooting Game", 120, 255, 255, 255);
    gameNameText->setLocalPosition((RTWidth - gameNameText->getScale().first) / 2, 300);

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
    emailBox = makeWidget<EditBoxWidget>("image/UIImage/box.png", "image/UIImage/caret.png", "e-mail",40, 255, 255, 255);
    emailBox->setScale(500 * canvasXRatio, 100 * canvasYRatio);
    emailBox->setLocalPosition((RTWidth - emailBox->getScale().first) / 2, 600);

    passwordBox = makeWidget<EditBoxWidget>("image/UIImage/box.png", "image/UIImage/caret.png", "password",40, 255, 255, 255);
    passwordBox->setScale(500 * canvasXRatio, 100 * canvasYRatio);
    passwordBox->setLocalPosition((RTWidth - passwordBox->getScale().first) / 2, 900);
}

void LoginCanvas::initButton()
{
    signInButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                    "", "sound/click.wav");
    signInButton->setScale(500 * canvasXRatio, 100 * canvasYRatio);
    signInButton->setLocalPosition((RTWidth - signInButton->getScale().first) / 2, 1100);
    signInButton->buttonUpEvent = [this]() mutable
    {
        std::string emailStr = emailBox->getContent();
        std::string passwordStr = passwordBox->getContent();
        Framework::auth->CreateUserWithEmailAndPassword(emailStr.c_str(), passwordStr.c_str());
        isCheckingSignIn = true;
        result = Framework::auth->CreateUserWithEmailAndPasswordLastResult();
    };

    resetButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                   "", "sound/click.wav");
    resetButton->setScale(500 * canvasXRatio, 100 * canvasYRatio);
    resetButton->setLocalPosition((RTWidth - signInButton->getScale().first) / 2, 1300);
    resetButton->buttonUpEvent = [this]() mutable
    {
        Framework::auth->SendPasswordResetEmail(this->emailBox->getContent().c_str());
        result2 = Framework::auth->SendPasswordResetEmailLastResult();
        isCheckingEmailSend = true;
    };

    loginButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                   "", "sound/click.wav");
    loginButton->setScale(500 * canvasXRatio, 100 * canvasYRatio);
    loginButton->setLocalPosition((RTWidth - signInButton->getScale().first) / 2, 1500);
    loginButton->buttonUpEvent = [this]() mutable
    {
        std::string emailStr = emailBox->getContent();
        std::string passwordStr = passwordBox->getContent();
        Framework::auth->SignInWithEmailAndPassword(emailStr.c_str(), passwordStr.c_str());
        result = Framework::auth->SignInWithEmailAndPasswordLastResult();
        isCheckingSignUp = true;
    };

    auto signButtonLoc = signInButton->getLocalPosition();
    auto signButtonSize = signInButton->getScale();
    signInText = makeWidget<TextWidget>("Sign in", 50, 255, 255, 255);
    signInText->setScale(signInText->getScale().first * canvasXRatio, signInText->getScale().second * canvasYRatio);
    auto signTextSize = signInText->getScale();
    signInText->setLocalPosition(signButtonLoc.first + (signButtonSize.first - signTextSize.first) / 2,
                                 signButtonLoc.second + (signButtonSize.second - signTextSize.second) / 2);

    auto loginButtonLoc = loginButton->getLocalPosition();
    auto loginButtonSize = loginButton->getScale();
    loginText = makeWidget<TextWidget>("Sign up", 50, 255, 255, 255);
    loginText->setScale(loginText->getScale().first * canvasXRatio, loginText->getScale().second * canvasYRatio);
    auto loginTextSize = loginText->getScale();
    loginText->setLocalPosition(loginButtonLoc.first + (loginButtonSize.first - loginTextSize.first) / 2,
                                loginButtonLoc.second + (loginButtonSize.second - loginTextSize.second) / 2);

    auto resetButtonLoc = resetButton->getLocalPosition();
    auto resetButtonSize = resetButton->getScale();
    resetText = makeWidget<TextWidget>("Send Password Reset Email", 40, 255, 255, 255);
    resetText->setScale(resetText->getScale().first * canvasXRatio, resetText->getScale().second * canvasYRatio);
    auto resetTextSize = resetText->getScale();
    resetText->setLocalPosition(resetButtonLoc.first + (resetButtonSize.first - resetTextSize.first) / 2,
                                resetButtonLoc.second + (resetButtonSize.second - resetTextSize.second) / 2);

    signInResultText = makeWidget<TextWidget>("Sign in success", 40, 255, 255, 255);
    signInResultText->setLocalPosition((RTWidth - signInResultText->getScale().first) / 2,h - 300);
    signInResultText->setScale(signInResultText->getScale().first * canvasXRatio,
                               signInResultText->getScale().second * canvasYRatio);
    signInResultText->setVisibility(false);
}