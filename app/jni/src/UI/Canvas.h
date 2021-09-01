#pragma once

#include <SDL.h>
#include <vector>

class Widget;
class ButtonWidget;
class EditBoxWidget;

class Canvas
{
public:
    Canvas() = delete;
    Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~Canvas();
    void addToViewport();
    void removeFromViewport();
    void addWidgetToBuffer(Widget* newWidget);
    void addButtonToBuffer(ButtonWidget* newWidget);
    void addEditBoxToBuffer(EditBoxWidget* newWidget);
    virtual void canvasRender();
    virtual void render();
    virtual bool handleEvent(SDL_Event& e) = 0;
    virtual void update(float deltaTime);
    void changeWindowAlphaValue(__uint8_t alpha);

protected:
    int w = 500;
    int h = 500;
    SDL_Texture* window = nullptr;
    int canvasWorldPosX = 0;
    int canvasWorldPosY = 0;
    bool visibility = false;
    std::vector<Widget*> canvasWidgets;
    std::vector<ButtonWidget*> canvasButtons;
    std::vector<EditBoxWidget*> editBoxes;

private:
    void createEmptyWindow();
};


