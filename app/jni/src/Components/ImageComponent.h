#pragma once

#include "HPrimitiveComponent.h"
#include <string>
#include <utility>

class SDL_Texture;
class SDL_Rect;
class SDL_Renderer;

class ImageComponent : public HPrimitiveComponent
{
public:
    ImageComponent() = default;
    ImageComponent(std::string path, const std::pair<int, int>& loc);
    virtual ~ImageComponent();

public:
    const std::pair<int, int> getImageSize();
    void setAlpha(__uint8_t alpha);
    void setImageColor(__uint8_t r, __uint8_t g, __uint8_t b);
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;

private:
    void loadImage(std::string path);

private:
    SDL_Texture* img = nullptr;
    SDL_Rect* imgRect = nullptr;
    __uint8_t alphaValue = 255;
};
