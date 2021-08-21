#include "TextWidget.h"
#include "../Components/TTFComponent.h"

TextWidget::TextWidget()
{
    text = new TTFComponent(0, 0, 24, 255, 0, 0, "font/EvilEmpire.ttf", "test TTF!!!", nullptr);
    auto scale = text->getScale();
    scaleX = scale.first;
    scaleY = scale.second;
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
    text->render();
}

void TextWidget::changeText(std::string content)
{
    text->changeText(content);
}
