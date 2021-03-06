#include "TextWidget.h"
#include "../Components/TTFComponent.h"

TextWidget::TextWidget(const std::string& content ,int fontSize, __uint8_t r, __uint8_t g, __uint8_t b, Canvas* owner):
Widget(owner)
{
    text = new TTFComponent(0, 0, fontSize, r, g, b, "font/EvilEmpire.ttf", content, nullptr);
    auto scale = text->getScale();
    setScale(scale.first, scale.second);
}

TextWidget::~TextWidget()
{
    delete text;
    text = nullptr;
}

void TextWidget::render()
{
    Widget::render();
    text->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
    text->setScale({scaleX, scaleY});
    text->render();
}

void TextWidget::update(const float deltaTime)
{
    if(visibility)
    {
        //나중에 애니메이션 추가시!
    }
}

void TextWidget::changeText(std::string content)
{
    text->changeText(content);
    auto scale = text->getScale();
    scaleX = scale.first;
    scaleY = scale.second;
}
