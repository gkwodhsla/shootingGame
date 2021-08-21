#include "ButtonWidget.h"
#include "../Components/ImageComponent.h"

ButtonWidget::ButtonWidget(const std::string &imagePath)
{
    buttonImg = new ImageComponent(imagePath, {0, 0}, nullptr);
    auto scale = buttonImg->getImageSize();
    setScale(scale.first, scale.second);
}

ButtonWidget::~ButtonWidget()
{
    delete buttonImg;
    buttonImg = nullptr;
}

void ButtonWidget::render()
{
    Widget::render();
    buttonImg->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
    buttonImg->setScale({scaleX, scaleY});
    buttonImg->render();
}

void ButtonWidget::changeImage(const std::string &imgPath)
{
    buttonImg->changeImage(imgPath);
}

void ButtonWidget::registerOnClickedEvent(std::function<void()> &func)
{
    buttonDown = func;
}

void ButtonWidget::checkIsClicked(int inputX, int inputY)
{
    auto buttonPos = getLocalPosition();
    auto buttonSize = buttonImg->getScale();
    if(buttonPos.first <= inputX && inputX <= buttonPos.first + buttonSize.first)
    {
        if(buttonPos.second <= inputY && inputY <= buttonPos.second + buttonSize.second)
        {
            buttonDown();
        }
    }
}
