#include "LoginCanvas.h"
#include "TitleController.h"
#include "../GlobalFunction.h"
#include "../DBManager.h"
#include <string>
#include <android/log.h>

LoginCanvas::LoginCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY) :
Canvas(canvasW, canvasH, canvasWorldX, canvasWorldY)
{
    backgroundImg = makeWidget<ImageWidget>("image/background/login.png", this);
    backgroundImg->setScale(RTWidth, RTHeight);
    backgroundImg->setLocalPosition(0, 0);

    gameNameText = makeWidget<TextWidget>("Shooting Game", 120, 255, 255, 255, this);
    gameNameText->setLocalPosition((RTWidth - gameNameText->getScale().first) / 2, 300);

    initEditBox();
    initButton();

    whiteBG = makeWidget<ImageWidget>("image/misc/whiteBG.png", this);
    whiteBG->setScale(RTWidth, RTHeight);
    whiteBG->setLocalPosition(0, 0);

    logoImg = makeWidget<ImageWidget>("image/misc/logo.png", this);
    logoImg->setScale(RTWidth, RTHeight);
    logoImg->setLocalPosition(0, 0);
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

bool LoginCanvas::handleEvent(const SDL_Event &e)
{
    if(isLogoFinish)
    {
        return Canvas::handleEvent(e);
    }
    return false;
}

void LoginCanvas::update(const float deltaTime)
{
    if(visibility)
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
                signInResultText->setLocalPosition((RTWidth - signInResultText->getScale().first) / 2,RTHeight - 300);
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
                }
                else
                {
                    signInResultText->changeText(result.error_message());
                }
                isShowSignInText = true;
                msgShowTime = maxMsgShowTime;
                signInResultText->setVisibility(true);
                signInResultText->setLocalPosition((RTWidth - signInResultText->getScale().first) / 2,RTHeight - 300);
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
                signInResultText->setLocalPosition((RTWidth - signInResultText->getScale().first) / 2,RTHeight - 300);
                isCheckingEmailSend = false;
            }
        }
        else if(isCheckingReadDataFromDB)
        {
            if (readDBResult.status() != firebase::kFutureStatusPending)
            {
                if (readDBResult.status() == firebase::kFutureStatusComplete &&
                    readDBResult.error() == firebase::database::kErrorNone)
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
        logoShowTime += deltaTime;
        if(logoShowTime<=1.0f)
        {
            logoImg->setAlpha(255.0f * logoShowTime);
        }
        if(logoShowTime >= 3.0f)
        {
            isLogoFinish = true;
            logoImg->setVisibility(false);
            whiteBG->setVisibility(false);
        }
    }
}

void LoginCanvas::initEditBox()
{
    emailBox = makeWidget<EditBoxWidget>("image/UIImage/box.png", "image/UIImage/caret.png", "e-mail",40, 255, 255, 255, this);
    emailBox->setScale(500, 100);
    emailBox->setLocalPosition((RTWidth - emailBox->getScale().first) / 2, 600);

    passwordBox = makeWidget<EditBoxWidget>("image/UIImage/box.png", "image/UIImage/caret.png", "password",40, 255, 255, 255, this);
    passwordBox->setScale(500, 100);
    passwordBox->setLocalPosition((RTWidth - passwordBox->getScale().first) / 2, 900);
}

void LoginCanvas::initButton()
{
    signInButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                    "", "sound/click.wav", this);
    signInButton->setScale(500, 100);
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
                                   "", "sound/click.wav", this);
    resetButton->setScale(500, 100);
    resetButton->setLocalPosition((RTWidth - signInButton->getScale().first) / 2, 1300);
    resetButton->buttonUpEvent = [this]() mutable
    {
        Framework::auth->SendPasswordResetEmail(this->emailBox->getContent().c_str());
        result2 = Framework::auth->SendPasswordResetEmailLastResult();
        isCheckingEmailSend = true;
    };

    loginButton = makeWidget<ButtonWidget>("image/UIImage/downButton.png", "image/UIImage/upButton.png",
                                   "", "sound/click.wav", this);
    loginButton->setScale(500, 100);
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
    signInText = makeWidget<TextWidget>("Sign up", 50, 255, 255, 255, this);
    signInText->setScale(signInText->getScale().first, signInText->getScale().second);
    auto signTextSize = signInText->getScale();
    signInText->setLocalPosition(signButtonLoc.first + (signButtonSize.first - signTextSize.first) / 2,
                                 signButtonLoc.second + (signButtonSize.second - signTextSize.second) / 2);

    auto loginButtonLoc = loginButton->getLocalPosition();
    auto loginButtonSize = loginButton->getScale();
    loginText = makeWidget<TextWidget>("Sign in", 50, 255, 255, 255, this);
    loginText->setScale(loginText->getScale().first, loginText->getScale().second);
    auto loginTextSize = loginText->getScale();
    loginText->setLocalPosition(loginButtonLoc.first + (loginButtonSize.first - loginTextSize.first) / 2,
                                loginButtonLoc.second + (loginButtonSize.second - loginTextSize.second) / 2);

    auto resetButtonLoc = resetButton->getLocalPosition();
    auto resetButtonSize = resetButton->getScale();
    resetText = makeWidget<TextWidget>("Send Password Reset Email", 40, 255, 255, 255, this);
    resetText->setScale(resetText->getScale().first, resetText->getScale().second);
    auto resetTextSize = resetText->getScale();
    resetText->setLocalPosition(resetButtonLoc.first + (resetButtonSize.first - resetTextSize.first) / 2,
                                resetButtonLoc.second + (resetButtonSize.second - resetTextSize.second) / 2);

    signInResultText = makeWidget<TextWidget>("Sign in success", 40, 255, 255, 255, this);
    signInResultText->setLocalPosition((RTWidth - signInResultText->getScale().first) / 2,RTHeight - 300);
    signInResultText->setVisibility(false);
    signInResultText->setScale(signInResultText->getScale().first,
                               signInResultText->getScale().second);
}