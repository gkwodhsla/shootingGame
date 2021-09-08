#include "ButtonWidget.h"
#include "../Components/ImageComponent.h"
#include "../Components/AudioComponent.h"

ButtonWidget::ButtonWidget(const std::string& downImgPath, const std::string& upImgPath,
                           const std::string& downSoundPath, const std::string& upSoundPath, Canvas* owner):Widget(owner)
{
    buttonUpImg = new ImageComponent(upImgPath, {0, 0}, nullptr);
    buttonDownImg = new ImageComponent(downImgPath, {0, 0}, nullptr);
    if(downSoundPath != "")
    {
        downSound = new AudioComponent(downSoundPath, buttonVolume, nullptr);
    }
    if(upSoundPath != "")
    {
        upSound = new AudioComponent(upSoundPath, buttonVolume, nullptr);
    }
    auto scale = buttonUpImg->getImageSize();
    setScale(scale.first, scale.second);
}

ButtonWidget::~ButtonWidget()
{
    delete buttonUpImg;
    buttonUpImg = nullptr;

    delete buttonDownImg;
    buttonDownImg = nullptr;

    if(downSound)
    {
        delete downSound;
        downSound = nullptr;
    }

    if(upSound)
    {
        delete upSound;
        upSound = nullptr;
    }
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

void ButtonWidget::update(float deltaTime)
{
    if(visibility)
    {
        if(isDown)
        {
            downTime += deltaTime;
            if(downTime > 0.5f)
            {
                if(buttonHoldEvent)
                {
                    holdCoolTime -= deltaTime;
                    if(holdCoolTime <= 0.0f)
                    {
                        buttonHoldEvent();
                        maxHoldCoolTime = holdCoolTime;
                    }
                }
            }
        }
        //나중에 UI애니메이션 추가되면 여기에서 해준다.
    }
}

void ButtonWidget::registerbuttonDownEvent(const std::function<void()> &func)
{
    buttonDownEvent = func;
}

void ButtonWidget::registerbuttonUpEvent(const std::function<void()>& func)
{
    buttonUpEvent = func;
}

void ButtonWidget::registerbuttonHoldEvent(const std::function<void()>& func)
{
    buttonHoldEvent = func;
}

bool ButtonWidget::checkIsClicked(int inputX, int inputY)
{
    bool isClicked = false;
    auto buttonPos = getLocalPosition();
    if(buttonPos.first <= inputX && inputX <= buttonPos.first + scaleX)
    {
        if(buttonPos.second <= inputY && inputY <= buttonPos.second + scaleY)
        {
            if(!isDown)
            {
                isDown = true;
                if(buttonDownEvent)
                {
                    buttonDownEvent();
                    if(downSound)
                    {
                        downSound->play();
                    }
                }
            }
            else
            {
                isDown = false;
                if(buttonUpEvent)
                {
                    buttonUpEvent();
                    downTime = 0.0f;
                    if(upSound)
                    {
                        upSound->play();
                    }
                }
            }
            isClicked = true;
        }
    }

    return isClicked;
}

bool ButtonWidget::checkIsHovering(int inputX, int inputY)
{
    bool isClicked = false;
    auto buttonPos = getLocalPosition();
    auto buttonSize = buttonDownImg->getScale();
    if(buttonPos.first <= inputX && inputX <= buttonPos.first + buttonSize.first)
    {
        if(buttonPos.second <= inputY && inputY <= buttonPos.second + buttonSize.second)
        {
            isClicked = true;
        }
    }

    return isClicked;
}

void ButtonWidget::setButtonUp()
{
    isDown = false;
}

void ButtonWidget::setButtonVolume(__uint8_t volume)
{
    buttonVolume = volume;
    if(downSound)
    {
        downSound->changeVolume(buttonVolume);
    }
    if(upSound)
    {
        upSound->changeVolume(buttonVolume);
    }
}