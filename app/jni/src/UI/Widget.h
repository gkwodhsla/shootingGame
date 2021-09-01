#pragma once
#include <utility>
#include <vector>

class Widget
{
public:
    Widget();
    virtual ~Widget() = 0;
    void setLocalPosition(int x, int y);
    void setScale(int scaleX, int scaleY);
    std::pair<int, int> getScale();
    std::pair<int, int> getLocalPosition();
    virtual void render();
    virtual void update(float deltaTime) = 0;
    bool getVisibility();
    void setVisibility(bool isVisible);

protected:
    int canvasX = 0;
    int canvasY = 0;
    int scaleX = 0;
    int scaleY = 0;
    bool visibility = true;
};