#pragma once

#include <SDL.h>

class TextWidget;
class ButtonWidget;

class Canvas
{
public:
    Canvas() = delete;
    Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY);
    virtual ~Canvas();
    void addToViewport();
    void removeFromViewport();
    virtual void canvasRender();
    virtual void render();
    virtual void handleEvent(SDL_Event& e) = 0;

protected:
    int w = 500;
    int h = 500;
    SDL_Texture* window = nullptr;
    int canvasWorldPosX = 0;
    int canvasWorldPosY = 0;
    bool visibility = false;

private:
    void createEmptyWindow();
};


