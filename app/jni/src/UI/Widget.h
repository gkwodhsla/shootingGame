#pragma once
#include <utility>
#include <vector>

class Widget
{
public:
    Widget();
    virtual ~Widget() = 0;
    void attachTo(Widget* parent);
    void setLocalPosition(int x, int y);
    void setScale(int scaleX, int scaleY);
    std::pair<int, int> getLocalPosition();
    virtual void render();

protected:
    Widget* parent = nullptr;
    std::vector<Widget*> children;
    int localX = 0;
    int localY = 0;
    int canvasX = 0;
    int canvasY = 0;
    int scaleX = 0;
    int scaleY = 0;
};