#include "EditBoxWidget.h"
#include "../Components/TTFComponent.h"
#include "../Components/ImageComponent.h"

EditBoxWidget::EditBoxWidget(const std::string &boxImagePath, const std::string &hintMessage,
                             int fontSize, __uint8_t r, __uint8_t g, __uint8_t b):r(r), g(g), b(b)
{
    if(hintMessage == "")
    {
        hintText = " ";
    }
    else
    {
        hintText = hintMessage;
    }
    text = new TTFComponent(0, 0, fontSize, 200, 200, 200, "font/EvilEmpire.ttf", hintText, nullptr);
    //힌트메시지는 연한 회색으로 출력한다.

    boxImg = new ImageComponent(boxImagePath, {0, 0}, nullptr);

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
}

void EditBoxWidget::update(float deltaTime)
{
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
        }
    }
    return isClicked;
}

void EditBoxWidget::setIsFocused(bool isFocused)
{
    this->isFocused = isFocused;
}

std::string EditBoxWidget::getContent() const
{
    return content;
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

}

void EditBoxWidget::eraseContent()
{

}
