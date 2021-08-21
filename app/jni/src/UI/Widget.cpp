#include "Widget.h"

Widget::Widget()
{

}

Widget::~Widget()
{

}

void Widget::attachTo(Widget* parent)
{
    parent->children.push_back(this);
    this->parent = parent;
    setLocalPosition(localX, localY);
}

void Widget::setLocalPosition(int x, int y)
{
    localX = x;
    localY = y;
    if(!parent)//만약 부모가 없다면 local이 canvs가 된다.
    {
        canvasX = localX;
        canvasY = localY;
    }
    else
    {
        canvasX = parent->canvasX + localX;
        canvasY = parent->canvasY + localY;
    }
}

std::pair<int, int> Widget::getLocalPosition()
{
    return std::make_pair(localX, localY);
}

void Widget::render()
{
    for(auto& child : children)
    {
        child->render();
    }
}