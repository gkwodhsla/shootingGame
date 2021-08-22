#pragma once

#include "Widget.h"
#include <functional>

class ImageComponent;

class ButtonWidget:public Widget
{
public:
    ButtonWidget() = delete;
    ButtonWidget(const std::string& downImgPath, const std::string& upImgPath);
    virtual ~ButtonWidget();
    virtual void render() override;
    void registerbuttonDownEvent(std::function<void()>& func);
    void registerbuttonUpEvent(std::function<void()>& func);
    void checkIsClicked(int inputX, int inputY);
    void setButtonUp();
public:
    std::function<void()> buttonDownEvent = nullptr;
    std::function<void()> buttonUpEvent = nullptr;
private:
    ImageComponent* buttonUpImg = nullptr;
    ImageComponent* buttonDownImg = nullptr;
    bool isDown = false;
};


