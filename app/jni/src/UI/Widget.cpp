#include "Widget.h"
#include "Canvas.h"
#include "../Framework.h"
Widget::Widget(Canvas* owner)
{
    this->owner = owner;
}

Widget::~Widget()
{

}

void Widget::setLocalPosition(int x, int y)
{
    canvasX = x;
    canvasY = y;
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
    return std::make_pair(canvasX, canvasY);
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

Canvas* Widget::getOwner()
{
    return owner;
}