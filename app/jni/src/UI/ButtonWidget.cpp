#include "ButtonWidget.h"
#include "../Components/ImageComponent.h"

ButtonWidget::ButtonWidget(const std::string& downImgPath, const std::string& upImgPath)
{
    buttonUpImg = new ImageComponent(upImgPath, {0, 0}, nullptr);
    buttonDownImg = new ImageComponent(downImgPath, {0, 0}, nullptr);

    auto scale = buttonUpImg->getImageSize();
    setScale(scale.first, scale.second);
}

ButtonWidget::~ButtonWidget()
{
    delete buttonUpImg;
    buttonUpImg = nullptr;

    delete buttonDownImg;
    buttonDownImg = nullptr;
}

void ButtonWidget::render()
{
    Widget::render();
    if(isDown)
    {
        buttonDownImg->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
        buttonDownImg->setScale({scaleX, scaleY});
        buttonDownImg->render();
    }
    else
    {
        buttonUpImg->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
        buttonUpImg->setScale({scaleX, scaleY});
        buttonUpImg->render();
    }
}

void ButtonWidget::registerbuttonDownEvent(std::function<void()> &func)
{
    buttonDownEvent = func;
}

void ButtonWidget::registerbuttonUpEvent(std::function<void()>& func)
{
    buttonUpEvent = func;
}

void ButtonWidget::checkIsClicked(int inputX, int inputY)
{
    auto buttonPos = getLocalPosition();
    auto buttonSize = buttonDownImg->getScale();
    if(buttonPos.first <= inputX && inputX <= buttonPos.first + buttonSize.first)
    {
        if(buttonPos.second <= inputY && inputY <= buttonPos.second + buttonSize.second)
        {
            if(!isDown)
            {
                isDown = true;
                if(buttonDownEvent)
                    buttonDownEvent();
            }
            else
            {
                isDown = false;
                if(buttonUpEvent)
                    buttonUpEvent();
            }
        }
    }
}

void ButtonWidget::setButtonUp()
{
    isDown = false;
}