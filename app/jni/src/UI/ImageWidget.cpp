#include "ImageWidget.h"
#include "../Components/ImageComponent.h"

ImageWidget::ImageWidget(const std::string &imagePath, Canvas* owner):Widget(owner)
{
    img = new ImageComponent(imagePath, {0, 0}, nullptr);
}

ImageWidget::~ImageWidget()
{
    delete img;
    img = nullptr;
}

void ImageWidget::changeImage(const std::string &imagePath)
{
    img->changeImage(imagePath);
}

void ImageWidget::setAlpha(__uint8_t alpha)
{
    img->setAlpha(alpha);
}

void ImageWidget::render()
{
    Widget::render();
    img->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
    img->setScale({scaleX, scaleY});
    img->render();
}

void ImageWidget::update(const float deltaTime)
{
    if(visibility)
    {
        //나중에 애니메이션 추가시!
    }
}