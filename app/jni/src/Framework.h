#pragma once
#include "Components/TTFComponent.h"
#include "firebase/app.h"
#include "firebase/auth.h"
#include "firebase/auth/credential.h"
#include "firebase/util.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Rect;
class HLevelBase;
class Canvas;
class SpritesheetComponent;

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
    static void changeLevel(HLevelBase* newLevel);
    static void eraseCanvas(Canvas* canvas);

private:
    static void initFirebase();

private:
    SDL_Window* window = nullptr;
    float accTime = 0.0f;
    TTFComponent* fpsText;

public:
    static SDL_Renderer* renderer;
    static SDL_Rect* screenRect;
    static int rendererWidth;
    static int rendererHeight;
    static HLevelBase* curLevel;
    static std::vector<Canvas*> worldUI;
    static firebase::App* app;
    static firebase::auth::Auth* auth;
};

