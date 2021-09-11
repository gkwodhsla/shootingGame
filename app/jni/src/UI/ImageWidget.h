#pragma once

#include "Widget.h"

class ImageComponent;

class ImageWidget: public Widget
{
public:
    ImageWidget() = delete;
    ImageWidget(const ImageWidget&) = delete;
    ImageWidget& operator=(const ImageWidget&) = delete;
    ImageWidget(const std::string& imagePath, Canvas* owner);
    virtual ~ImageWidget();
    void changeImage(const std::string& imagePath);
    void setAlpha(__uint8_t alpha);
    virtual void render() override;
    virtual void update(const float deltaTime) override;
private:
    ImageComponent* img = nullptr;
};

