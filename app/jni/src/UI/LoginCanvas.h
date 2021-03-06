#pragma once

#include "Canvas.h"
#include "../Framework.h"
#include "firebase/app.h"
#include "firebase/util.h"
#include "firebase/database.h"

class ButtonWidget;
class TextWidget;
class ImageWidget;
class EditBoxWidget;

class LoginCanvas :public Canvas
{
public:
    LoginCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    LoginCanvas() = delete;
    LoginCanvas(const LoginCanvas&) = delete;
    LoginCanvas& operator=(const LoginCanvas&) = delete;
    virtual ~LoginCanvas();
    void canvasRender() override;
    void render() override;
    bool handleEvent(const SDL_Event& e) override;
    void update(const float deltaTime) override;

private:
    void initEditBox();
    void initButton();

private:
    ImageWidget* backgroundImg = nullptr;
    TextWidget* gameNameText = nullptr;
    EditBoxWidget* emailBox = nullptr;
    EditBoxWidget* passwordBox = nullptr;
    ButtonWidget* signInButton = nullptr;
    ButtonWidget* loginButton = nullptr;
    ButtonWidget* resetButton = nullptr;
    TextWidget* signInText = nullptr;
    TextWidget* resetText = nullptr;
    TextWidget* loginText = nullptr;
    TextWidget* signInResultText = nullptr;
    ImageWidget* whiteBG = nullptr;
    ImageWidget* logoImg = nullptr;
    bool isCheckingSignIn = false;
    bool isCheckingSignUp = false;
    bool isCheckingEmailSend = false;
    bool isCheckingReadDataFromDB = false;
    bool isShowSignInText = false;
    bool isLogoFinish = false;
    float logoShowTime = 0.0f;
    float msgShowTime = 2.0f;
    const float maxMsgShowTime = 2.0f;
    firebase::Future<firebase::auth::User*> result;
    firebase::Future<void> result2;
    firebase::Future<firebase::database::DataSnapshot> readDBResult;
};