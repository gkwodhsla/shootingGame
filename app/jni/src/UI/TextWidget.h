#pragma once

#include "Widget.h"

class TTFComponent;

class TextWidget: public Widget
{
public:
    TextWidget();
    virtual ~TextWidget();
    virtual void render() override;
    void changeText(std::string content);
private:
    TTFComponent* text = nullptr;
};