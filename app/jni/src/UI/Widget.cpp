#include "Widget.h"

Widget::Widget()
{

}

Widget::~Widget()
{

}

void Widget::setLocalPosition(int x, int y)
{
    localX = x;
    localY = y;
    canvasX = localX;
    canvasY = localY;
}

void Widget::setScale(int scaleX, int scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

std::pair<int, int> Widget::getScale()
{
    return std::make_pair(scaleX, scaleY);
}

std::pair<int, int> Widget::getLocalPosition()
{
    return std::make_pair(localX, localY);
}

void Widget::render()
{

}

bool Widget::getVisibility()
{
    return visibility;
}

void Widget::setVisibility(bool isVisible)
{
    visibility = isVisible;
}