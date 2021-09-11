//
// Created by lenovo on 2021-08-07.
//

#include "ImageComponent.h"
#include "../Framework.h"
#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>
#include "../Actors/HActor.h"

ImageComponent::ImageComponent(HActor* owner)
{
    img = nullptr;
    imgRect = new SDL_Rect();
    clipRect = new SDL_Rect();
    localLocation.first = 0.0f;
    localLocation.second = 0.0f;
    imgRect->x = localLocation.first;
    imgRect->y = localLocation.second;
    localRotation = 0.0f;
    this->owner = owner;
}

ImageComponent::ImageComponent(const std::string& path, const std::pair<int, int>& loc, HActor* owner)
{
    img = nullptr;
    loadImage(path);
    imgRect = new SDL_Rect();
    clipRect = new SDL_Rect();
    int w = 0, h = 0;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    imgRect->w = w;
    imgRect->h = h;
    scale.first = w;
    scale.second = h;
    localLocation.first = loc.first;
    localLocation.second = loc.second;
    imgRect->x = localLocation.first;
    imgRect->y = localLocation.second;

    localRotation = 0.0f;
    SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(img, alphaValue);
    setOwner(owner);
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

std::pair<int, int> ImageComponent::getImageSize()
{
    return std::make_pair(imgRect->w, imgRect->h);
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

void ImageComponent::setImageFlip(SDL_RendererFlip flipState)
{
    flip = flipState;
}

void ImageComponent::render()
{
    HPrimitiveComponent::render();

    if(visibility)
    {
        SDL_Rect dstRect;
        dstRect.x = int(worldLocation.first);//imgRect->x;
        dstRect.y = int(worldLocation.second);//imgRect->y;
        dstRect.w = scale.first;
        dstRect.h = scale.second;

        if (!isEnableClipDraw) {
            SDL_RenderCopyEx(Framework::renderer, img, NULL, &dstRect,
                             worldRotation, NULL, flip);
        } else {
            SDL_RenderCopyEx(Framework::renderer, img, clipRect, &dstRect,
                             worldRotation, NULL, flip);
        }
    }
}

void ImageComponent::update(const float deltaTime)
{
    HPrimitiveComponent::update(deltaTime);
}

void ImageComponent::changeImage(const std::string &path)
{
    if(img)
    {
        SDL_DestroyTexture(img);
        img = nullptr;
    }
    loadImage(path);
    int w = 0, h = 0;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    imgRect->w = w;
    imgRect->h = h;
    imgRect->x = localLocation.first;
    imgRect->y = localLocation.second;
    scale.first = w;
    scale.second = h;
    SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(img, alphaValue);
}

void ImageComponent::referencingOtherImgCompsImg(const ImageComponent& other)
{
    this->img = other.img;
    imgRect->w = other.imgRect->w;
    imgRect->h = other.imgRect->h;
    imgRect->x = other.localLocation.first;
    imgRect->y = other.localLocation.second;
    scale.first = other.scale.first;
    scale.second = other.scale.second;
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

void ImageComponent::loadImage(const std::string& path)
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
}


