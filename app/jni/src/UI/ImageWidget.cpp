#include "ImageWidget.h"
#include "../Components/ImageComponent.h"

ImageWidget::ImageWidget(const std::string &imagePath)
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

void ImageWidget::render()
{
    Widget::render();
    img->setComponentLocalLocation(std::make_pair(float(canvasX), float(canvasY)));
    img->setScale({scaleX, scaleY});
    img->render();
}