#pragma once

#include <SDL.h>

class TextWidget;
class ButtonWidget;

class Canvas
{
public:
    Canvas();
    Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY, int canvasScaleX, int canvasScaleY);
    virtual ~Canvas();
    void addToViewport();
    void removeFromViewport();
    void canvasRender();
    void render();
    void handleEvent(SDL_Event& e);

private:
    void createEmptyWindow();

private:
    int w = 500;
    int h = 500;
    SDL_Texture* window = nullptr;
    int canvasWorldPosX = 0;
    int canvasWorldPosY = 0;
    int canvasScaleX = 500;
    int canvasScaleY = 500;
    bool visibility = false;
    ButtonWidget* testButton;
};


