#pragma once

#include "Widget.h"
#include <string>
class TTFComponent;
class ImageComponent;

class EditBoxWidget: public Widget
{
public:
    EditBoxWidget(const std::string& boxImagePath, const std::string& caretImagePath, const std::string& hintMessage,
                  int fontSize, __uint8_t r, __uint8_t g, __uint8_t b, Canvas* owner);
    virtual ~EditBoxWidget();
    void render() override;
    void update(const float deltaTime) override;
    void changeText(const std::string& content);
    bool checkIsClicked(int inputX, int inputY);
    void swapText();
    void addContent(const std::string& character);
    void eraseContent();

public:
    void setIsFocused(bool isFocused);
    std::string getContent() const;
    bool getIsFocused() const;

private:
    void calcCurCaretPos();

private:
    TTFComponent* text = nullptr;
    ImageComponent* boxImg = nullptr;
    ImageComponent* caretImg = nullptr;
    std::string content = " ";
    std::string hintText = " ";
    int fontSize = 0;
    __uint8_t r = 255;
    __uint8_t g = 255;
    __uint8_t b = 255;
    bool isFocused = false;
    bool isCaretShow = false;
    float coolTime = 0.0f;
    int caretIndex = 0;
    int caretXPos = 0;
    int characterSize = 0;
    static const float maxCoolTime;
    static const int caretYInterpValue;
};