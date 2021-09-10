#pragma once
#include <utility>
#include <vector>

class Canvas;

class Widget
{
public:
    Widget() = delete;
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;
    Widget(Canvas* owner);
    virtual ~Widget() = 0;
    void setLocalPosition(int x, int y);
    void setScale(int scaleX, int scaleY, bool isDrawRenderTargetSize = false);
    std::pair<int, int> getScale();
    std::pair<int, int> getLocalPosition();
    virtual void render();
    virtual void update(const float deltaTime) = 0;
    bool getVisibility();
    void setVisibility(bool isVisible);
    Canvas* getOwner();

protected:
    int canvasX = 0;
    int canvasY = 0;
    int scaleX = 0;
    int scaleY = 0;
    bool visibility = true;
    Canvas* owner;
};