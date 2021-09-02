#pragma once

#include "Canvas.h"

class ButtonWidget;
class TextWidget;
class ImageWidget;
class EditBoxWidget;

class LoginCanvas :public Canvas
{
public:
    LoginCanvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~LoginCanvas();
    void canvasRender() override;
    void render() override;
    bool handleEvent(SDL_Event& e) override;
    void update(float deltaTime) override;

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
    TextWidget* signInText = nullptr;
    TextWidget* loginText = nullptr;
};