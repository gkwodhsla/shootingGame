#pragma once

#include "Widget.h"
#include <string>
class TTFComponent;
class ImageComponent;

class EditBoxWidget: public Widget
{
public:
    EditBoxWidget(const std::string& boxImagePath, const std::string& hintMessage,
                  int fontSize, __uint8_t r, __uint8_t g, __uint8_t b);
    virtual ~EditBoxWidget();
    void render() override;
    void update(float deltaTime) override;
    void changeText(const std::string& content);
    bool checkIsClicked(int inputX, int inputY);
    void swapText();
    void addContent(const std::string& character);
    void eraseContent();

public:
    void setIsFocused(bool isFocused);
    std::string getContent() const;

private:
    TTFComponent* text = nullptr;
    ImageComponent* boxImg = nullptr;
    std::string content = " ";
    std::string hintText = " ";
    __uint8_t r = 255;
    __uint8_t g = 255;
    __uint8_t b = 255;
    bool isFocused = false;
};