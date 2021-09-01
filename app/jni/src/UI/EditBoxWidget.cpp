#include "EditBoxWidget.h"
#include "../Components/TTFComponent.h"
#include "../Components/ImageComponent.h"
#include <android/log.h>

const int EditBoxWidget::caretYInterpValue = 50;
const float EditBoxWidget::maxCoolTime = 0.3f;

EditBoxWidget::EditBoxWidget(const std::string &boxImagePath, const std::string& caretImagePath, const std::string &hintMessage,
                             int fontSize, __uint8_t r, __uint8_t g, __uint8_t b):fontSize(fontSize), r(r), g(g), b(b)
{
    if(hintMessage == "")
    {
        hintText = " ";
    }
    else
    {
        hintText = hintMessage;
    }
    text = new TTFComponent(0, 0, fontSize, 200, 200, 200, "font/EvilEmpire.ttf", "abcdefghijklmnopqrstuvwxyz", nullptr);
    characterSize = text->getScale().first / 26;
    text->changeText(hintMessage);
    //힌트메시지는 연한 회색으로 출력한다.

    boxImg = new ImageComponent(boxImagePath, {0, 0}, nullptr);

    caretImg = new ImageComponent(caretImagePath, {0, 0}, nullptr);
    caretImg->setScale({5, caretYInterpValue});

}

EditBoxWidget::~EditBoxWidget()
{
    delete text;
    text = nullptr;

    delete boxImg;
    boxImg = nullptr;
}

void EditBoxWidget::render()
{
    Widget::render();
    boxImg->setScale({scaleX,scaleY});
    boxImg->setComponentLocalLocation({canvasX, canvasY});
    boxImg->render();
    text->setComponentLocalLocation({canvasX + 30, canvasY + (boxImg->getScale().second - text->getScale().second) / 2});
    text->render();
    if(isFocused && isCaretShow)
    {
        caretImg->setComponentLocalLocation({canvasX + caretXPos + 30,
                                             canvasY + (scaleY - caretYInterpValue) / 2});
        caretImg->render();
    }
}

void EditBoxWidget::update(float deltaTime)
{
    if(isFocused)
    {
        coolTime -= deltaTime;
        if(coolTime <= 0.0f)
        {
            coolTime = maxCoolTime;
            if(isCaretShow)
            {
                isCaretShow = false;
            }
            else
            {
                isCaretShow = true;
            }
        }
    }
    //나중에 업데이트 할 항목이 있다면 추가한다.
}

void EditBoxWidget::changeText(const std::string &content)
{
    text->changeText(content);
}

bool EditBoxWidget::checkIsClicked(int inputX, int inputY)
{
    bool isClicked = false;
    auto boxPos = getLocalPosition();
    auto boxSize = boxImg->getScale();
    if(boxPos.first <= inputX && inputX <= boxPos.first + boxSize.first)
    {
        if(boxPos.second <= inputY && inputY <= boxPos.second + boxSize.second)
        {
            isClicked = true;
            isFocused = true;
            caretIndex = (inputX - canvasX) / characterSize;
            if(caretIndex <= 0)
            {
                caretIndex = 1;
            }
            if(caretIndex > content.size())
            {
                caretIndex = content.size();
            }
            calcCurCaretPos();
        }
    }
    return isClicked;
}

void EditBoxWidget::setIsFocused(bool isFocused)
{
    this->isFocused = isFocused;
    if(isFocused)
    {
        isCaretShow = true;
        coolTime = maxCoolTime;
    }
}

std::string EditBoxWidget::getContent() const
{
    return content.substr(1, content.size() - 1);
}

bool EditBoxWidget::getIsFocused() const
{
    return isFocused;
}

void EditBoxWidget::swapText() //만약 포커스되면 힌트메시지를 지워버리고, 포커스상태가 아니고 실제 콘텐츠가 비어있다면 힌트 메시지를 다시 보여준다.
{
    if(isFocused)
    {
        text->changeColor(r, g, b);
        text->changeText(content);
    }
    else
    {
        if(content == " ")
        {
            text->changeColor(200, 200, 200);
            text->changeText(hintText);
        }
    }
}

void EditBoxWidget::addContent(const std::string& character)
{
    content.insert(caretIndex, character);
    ++caretIndex;
    text->changeText(content);
    calcCurCaretPos();
}

void EditBoxWidget::eraseContent()
{
    if(content.size() > 0 && caretIndex > 1) // 지울 내용이 있으면 지운다.
    {
        content.erase(caretIndex - 1, 1);
        if(content.size() == 0)
        {
            content = " ";
            caretIndex = 1;
        }
        text->changeText(content);
        --caretIndex;
        calcCurCaretPos();
    }
}

void EditBoxWidget::calcCurCaretPos()
{
    std::string temp;
    for(int i = 0; i < caretIndex; ++i)
    {
        temp += content[i];
    }
    text->changeText(temp);
    caretXPos = text->getScale().first;
    text->changeText(content);
}