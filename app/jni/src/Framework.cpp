//
// Created by lenovo on 2021-08-07.
//

#include "Framework.h"
#include "Level/HLevelBase.h"
#include "Level/MainLevel.h"
#include <android/log.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>

using namespace std;

SDL_Renderer* Framework::renderer = nullptr;
SDL_Rect* Framework::screenRect = nullptr;
HLevelBase* Framework::curLevel = nullptr;
int Framework::rendererWidth = 0;
int Framework::rendererHeight = 0;
Framework::Framework()
{
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "SDL could not initialize SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "Warning: Linear texture filtering not enabled!");
        }
    }
    SDL_DisplayMode displayMode;

    screenRect = new SDL_Rect();
    if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
    {
        screenRect->w = displayMode.w;
        screenRect->h = displayMode.h;
    }

    //Create window
    window = SDL_CreateWindow( "Airplane Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                screenRect->w, screenRect->h, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        //추후 VSYNC를 위해 SDL_RENDERER_PRESENTVSYNC 옵션 추가 가능
        if(renderer == NULL)
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            int imgFlags = IMG_INIT_PNG;

            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                    "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }

            if( TTF_Init() == -1 )
            {
                __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                    "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            }
        }
    }
    int getW;
    int getH;
    SDL_GetRendererOutputSize(Framework::renderer,
                              &getW, &getH);
    rendererWidth = getW;
    rendererHeight = getH;

    curLevel = new MainLevel();

}

Framework::~Framework()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    delete screenRect;
    screenRect = nullptr;
    delete curLevel;
    curLevel = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Framework::handleEvent()
{
    SDL_Event e;
    SDL_Point touchLocation;
    while(SDL_PollEvent(&e) != 0) //이벤트 큐의 이벤트를 모조리 꺼낸다.
    {
        curLevel->handleEvent(e);
    }
}

void Framework::update(float deltaTime)
{
    curLevel->update(deltaTime);
}

//BackgroundActor myBG;
void Framework::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    curLevel->render();
    SDL_RenderPresent(renderer);
}

void Framework::startGame()
{
    float deltaTime = 0.0f;
    while(1)
    {
        chrono::system_clock::time_point start = chrono::system_clock::now();
        handleEvent();
        update(deltaTime);
        render();
        chrono::duration<double> sec = chrono::system_clock::now() - start;
        accTime += sec.count();
        deltaTime = sec.count();
    }
}