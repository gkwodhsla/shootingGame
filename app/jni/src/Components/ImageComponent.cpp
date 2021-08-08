//
// Created by lenovo on 2021-08-07.
//

#include "ImageComponent.h"
#include "../Framework.h"
#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>

ImageComponent::ImageComponent(std::string path, const std::pair<int, int>& loc)
{
    img = nullptr;
    loadImage(path);
    imgRect = new SDL_Rect();
    clipRect = new SDL_Rect();
    int w = 0, h = 0;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    imgRect->w = w;
    imgRect->h = h;
    localLocation.first = loc.first;
    localLocation.second = loc.second;
    imgRect->x = localLocation.first;
    imgRect->y = localLocation.second;
    localRotation = 0.0f;
    SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(img, alphaValue);
}
ImageComponent::~ImageComponent()
{
    SDL_DestroyTexture(img);
    img = nullptr;
    delete imgRect;
    imgRect = nullptr;
    delete clipRect;
    clipRect = nullptr;
}

const std::pair<int, int> ImageComponent::getImageSize()
{
    return scale;
}

void ImageComponent::setAlpha(__uint8_t alpha)
{
    alphaValue = alpha;
    SDL_SetTextureAlphaMod(img, alphaValue);
}

void ImageComponent::setImageColor(__uint8_t r, __uint8_t g, __uint8_t b)
{
    SDL_SetTextureColorMod(img, r, g, b);
}

void ImageComponent::render()
{
    if(!isEnableClipDraw)
    {
        SDL_RenderCopyEx(Framework::renderer, img, NULL, imgRect,
                         localRotation, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(Framework::renderer, img, clipRect, imgRect,
                         localRotation, NULL, SDL_FLIP_NONE);
    }
    for(auto&element:children)
    {
        element->render();
    }
}

void ImageComponent::update(float deltaTime)
{

}

void ImageComponent::setClipDraw(bool isClipDraw)
{
    isEnableClipDraw = isClipDraw;
}

void ImageComponent::setClipRect(int x, int y, int w, int h)
{
    clipRect->x = x;
    clipRect->y = y;
    clipRect->w = w;
    clipRect->h = h;

}


void ImageComponent::loadImage(std::string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "SDL_image Create Surface Failed! Error: %s\n", IMG_GetError());
    }
    else
    {
        img = SDL_CreateTextureFromSurface(Framework::renderer, loadedSurface);
        if(!img)
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "SDL_image Create Texture Failed! Error: %s\n", IMG_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                        "Image load success");
}


