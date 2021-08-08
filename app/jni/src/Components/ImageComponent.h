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
    void render() override;
    void update(float deltaTime) override;
    void changeImage(const std::string& path);

public:
    void setClipDraw(bool isClipDraw);
    void setClipRect(int x, int y, int w, int h);
private:
    void loadImage(const std::string& path);

private:
    SDL_Texture* img = nullptr;
    SDL_Rect* imgRect = nullptr;
    SDL_Rect* clipRect = nullptr;
    __uint8_t alphaValue = 255;
    bool isEnableClipDraw = false;
};
