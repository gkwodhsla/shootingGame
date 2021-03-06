#include "Framework.h"
#include "DBManager.h"
#include "Level/HLevelBase.h"
#include "Level/MainLevel.h"
#include "Level/TitleLevel.h"
#include "Components/SpritesheetComponent.h"
#include <android/log.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <chrono>
#include "UI/Canvas.h"

using namespace std;

SDL_Renderer* Framework::renderer = nullptr;
SDL_Rect* Framework::screenRect = nullptr;
HLevelBase* Framework::curLevel = nullptr;
int Framework::rendererWidth = 0;
int Framework::rendererHeight = 0;
int Framework::RTWidth = 1080;
int Framework::RTHeight = 1920;
std::vector<Canvas*> Framework::worldUI;
firebase::App* Framework::app = nullptr;
firebase::auth::Auth* Framework::auth = nullptr;
std::string Framework::UID = "";
DBManager* Framework::dbManager = nullptr;
Framework* Framework::instance = nullptr;

Framework::Framework()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
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
                                screenRect->w, screenRect->h, SDL_WINDOW_SHOWN);

    if( window == NULL )
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);
        if(renderer == NULL)
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            createRenderTarget();

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

            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
            {
                __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                    "SDL_mixer could not initialize! SDL_ttf Error: %s\n", Mix_GetError());
            }
        }
    }
    int getW;
    int getH;
    SDL_GetRendererOutputSize(Framework::renderer,
                              &getW, &getH);
    rendererWidth = getW;
    rendererHeight = getH;

    initFirebase();

    curLevel = GlobalFunction::createNewObject<TitleLevel>();
    curLevel->enter();

    dbManager = DBManager::getInstance();

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

    delete app;
    app = nullptr;

    delete dbManager;
    dbManager = nullptr;

    SDL_DestroyTexture(renderTarget);
    renderTarget = nullptr;
    for(auto& canvas:worldUI)
    {
        if(canvas)
        {
            delete canvas;
            canvas = nullptr;
        }
    }
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Framework::handleEvent()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0) //????????? ?????? ???????????? ????????? ?????????.
    {
        curLevel->handleEvent(e);
    }
}

void Framework::update(float deltaTime)
{
    for(auto&canvas : worldUI)
    {
        canvas->update(deltaTime);
    }
    curLevel->update(deltaTime);
}

void Framework::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    for(auto& canvas:worldUI)
    {
        canvas->canvasRender();
    }
    SDL_SetRenderTarget(Framework::renderer, renderTarget);
    SDL_SetRenderDrawColor(Framework::renderer, 0xff, 0xff, 0xff, 0);
    SDL_RenderClear(Framework::renderer);
    curLevel->render();
    SDL_SetRenderTarget(Framework::renderer, nullptr);
    //???????????? ????????????????????? ????????? ????????? ?????? ???????????? ????????? ????????????.

    SDL_RenderCopyEx(Framework::renderer, renderTarget, NULL, NULL,
                     0.0f, NULL, SDL_FLIP_NONE);

    for(auto& canvas:worldUI)
    {
        canvas->render();
    }
    SDL_RenderPresent(renderer);
}

void Framework::startGame()
{
    float deltaTime = 0.0f;

    while(1)
    {
        chrono::system_clock::time_point start = chrono::system_clock::now();
        if(curLevel)
        {
            handleEvent();
            update(deltaTime);
            render();
        }
        chrono::duration<double> sec = chrono::system_clock::now() - start;
        accTime += sec.count();
        deltaTime = sec.count();
    }
}

void Framework::changeRenderTargetSize(int width, int height)
{
    SDL_DestroyTexture(renderTarget);
    renderTarget = nullptr;
    RTWidth = width;
    RTHeight = height;
    createRenderTarget();
}

void Framework::changeLevel(HLevelBase* newLevel)
{
    curLevel->exit();
    delete curLevel;
    curLevel = nullptr;
    curLevel = newLevel;
    newLevel->enter();
}

void Framework::initFirebase()
{
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();

    jobject activity = (jobject)SDL_AndroidGetActivity();
#if defined(__ANDROID__)
    app = firebase::App::Create(firebase::AppOptions(), env, activity);
#else
    app = firebase::App::Create(firebase::AppOptions());
#endif  // defined(__ANDROID__)
    if(!app)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Create android app failed...");
    }

    auth = firebase::auth::Auth::GetAuth(app);

    if(!auth)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Create android auth failed...");
    }
}

void Framework::createRenderTarget()
{
    renderTarget = SDL_CreateTexture(Framework::renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET
                                     , Framework::RTWidth, Framework::RTHeight);
}

Framework* Framework::getInstance()
{
    if(!instance)
    {
        instance = new Framework();
    }
    return instance;
}