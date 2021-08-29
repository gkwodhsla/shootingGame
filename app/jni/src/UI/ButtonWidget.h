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
    virtual void update(float deltaTime) override;
    void registerbuttonDownEvent(const std::function<void()>& func);
    void registerbuttonUpEvent(const std::function<void()>& func);
    void registerbuttonHoldEvent(const std::function<void()>& func);
    bool checkIsClicked(int inputX, int inputY);
    bool checkIsHovering(int inputX, int inputY);
    void setButtonUp();
public:
    std::function<void()> buttonDownEvent = nullptr;
    std::function<void()> buttonUpEvent = nullptr;
    std::function<void()> buttonHoldEvent = nullptr;
private:
    ImageComponent* buttonUpImg = nullptr;
    ImageComponent* buttonDownImg = nullptr;
    bool isDown = false;
    float downTime = 0.0f;
    float holdCoolTime = 0.1f;
    float maxHoldCoolTime = 0.1f;
};


