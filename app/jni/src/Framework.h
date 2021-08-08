//
// Created by lenovo on 2021-08-07.
//

#pragma once

class SDL_Window;
class SDL_Renderer;
class SDL_Rect;
class HLevelBase;

class Framework
{
public:
    Framework();
    virtual ~Framework();

public:
    void handleEvent();
    void update(float deltaTime);
    void render();
    void startGame();

private:
    SDL_Window* window = nullptr;
    HLevelBase* curLevel;
    float accTime = 0.0f;
public:
    static SDL_Renderer* renderer;
    static SDL_Rect* screenRect;
    static int rendererWidth;
    static int rendererHeight;
};

