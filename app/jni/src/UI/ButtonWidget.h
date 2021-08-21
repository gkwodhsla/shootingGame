#pragma once

#include "Widget.h"
#include <functional>

class ImageComponent;

class ButtonWidget:public Widget
{
public:
    ButtonWidget() = delete;
    ButtonWidget(const std::string& imagePath);
    virtual ~ButtonWidget();
    virtual void render() override;
    void changeImage(const std::string& imgPath);
    void registerOnClickedEvent(std::function<void()>& func);
    void checkIsClicked(int inputX, int inputY);
public:
    std::function<void()> buttonDown = nullptr;
private:
    ImageComponent* buttonImg = nullptr;
};


