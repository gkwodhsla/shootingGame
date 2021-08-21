#pragma once

#include "Widget.h"

class ImageComponent;

class ImageWidget: public Widget
{
public:
    ImageWidget() = delete;
    ImageWidget(const std::string& imagePath);
    virtual ~ImageWidget();
    void changeImage(const std::string& imagePath);
    virtual void render() override;
private:
    ImageComponent* img = nullptr;
};

