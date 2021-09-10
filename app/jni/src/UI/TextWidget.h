#pragma once

#include "Widget.h"

class TTFComponent;

class TextWidget: public Widget
{
public:
    TextWidget(const std::string& content ,int fontSize, __uint8_t r, __uint8_t g, __uint8_t b, Canvas* owner);
    virtual ~TextWidget();
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void changeText(std::string content);
private:
    TTFComponent* text = nullptr;
};