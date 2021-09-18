#include "TTFComponent.h"
#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>
#include "../Framework.h"
#include "../Actors/HActor.h"

TTFComponent::TTFComponent(int x, int y, int fontSize, __uint8_t r, __uint8_t g, __uint8_t b,
                           std::string fontPath, std::string text, HActor* owner)
{
    this->setComponentLocalLocation(std::make_pair(float(x), float(y)));
    this->setComponentLocalRotation(0.0f);
    this->fontSize = fontSize;
    curFont = TTF_OpenFont(fontPath.c_str(), fontSize);
    this->r = r;
    this->g = g;
    this->b = b;
    this->text = text;
    texture = nullptr;
    loadText(text, r, g, b);
    this->owner = owner;
}

TTFComponent::~TTFComponent()
{
    TTF_CloseFont(curFont);
    curFont = nullptr;
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void TTFComponent::render()
{
    HPrimitiveComponent::render();

    SDL_Rect dstRect;
    dstRect.x = int(worldLocation.first);
    dstRect.y = int(worldLocation.second);
    dstRect.w = scale.first;
    dstRect.h = scale.second;

    if(visibility)
    {
        SDL_RenderCopy(Framework::renderer, texture, nullptr, &dstRect);
    }
}

void TTFComponent::update(const float deltaTime)
{
    HPrimitiveComponent::update(deltaTime);
}

void TTFComponent::changeText(std::string text)
{
    loadText(text, r, g, b);
}

void TTFComponent::changeColor( __uint8_t r, __uint8_t g, __uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void TTFComponent::loadText(std::string text, __uint8_t r, __uint8_t g, __uint8_t b)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    SDL_Surface* textSurface = TTF_RenderText_Solid(curFont, text.c_str(), color);
    if (textSurface == nullptr)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Unable to render text surface SDL_ttf Error: %s", TTF_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(Framework::renderer, textSurface);
        if (texture == nullptr)
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "Unable to create texture from rendered text SDL Error: %s", SDL_GetError());
        }
        scale.first = textSurface->w;
        scale.second = textSurface->h;
        SDL_FreeSurface(textSurface);
    }
}
