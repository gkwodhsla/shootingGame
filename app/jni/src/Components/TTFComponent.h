#pragma once

#include "HPrimitiveComponent.h"
#include <SDL_ttf.h>

class SDL_Texture;
class HActor;
class TTFComponent :public HPrimitiveComponent
{
public:
    TTFComponent() = delete;
    TTFComponent(int x, int y, int fontSize, __uint8_t r, __uint8_t g, __uint8_t b, std::string fontPath , std::string text,
                 HActor* owner);
    virtual ~TTFComponent();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    void changeText(std::string text);
    void changeColor( __uint8_t r, __uint8_t g, __uint8_t b);

private:
    TTF_Font* curFont = nullptr;
    SDL_Texture* texture = nullptr;
    int textWidth = 0;
    int textHeight = 0;
    int fontSize = 0;
    __uint8_t r = 0;
    __uint8_t g = 0;
    __uint8_t b = 0;
    std::string text = "";

private:
    void loadText(std::string text, __uint8_t r, __uint8_t g, __uint8_t b);
};