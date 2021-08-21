#include "Canvas.h"
#include "../Framework.h"
#include "TextWidget.h"
#include "ButtonWidget.h"
#include <android/log.h>
Canvas::Canvas()
{
    createEmptyWindow();
    testButton = new ButtonWidget("image/UIbutton/playButton.png");
    testButton->buttonDown = [](){__android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                                      "Button Down");};
    Framework::worldUI.push_back(this);
}

Canvas::Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY, int canvasScaleX, int canvasScaleY):
w(canvasW), h(canvasH), canvasWorldPosX(canvasWorldX), canvasWorldPosY(canvasWorldY), canvasScaleX(canvasScaleX),
canvasScaleY(canvasScaleY)
{
    createEmptyWindow();
    Framework::worldUI.push_back(this);
}

Canvas::~Canvas()
{
    SDL_DestroyTexture(window);
    window = nullptr;
    delete testButton;
    testButton = nullptr;
}

void Canvas::addToViewport()
{
    visibility = true;
}

void Canvas::removeFromViewport()
{
    visibility = false;
}

void Canvas::canvasRender()
{
    if(visibility)
    {
        SDL_SetRenderTarget(Framework::renderer, window);
        SDL_SetRenderDrawColor(Framework::renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(Framework::renderer);
        //이곳에서 위젯들을 모두 그려준다.
        testButton->render();
        //이곳에서 위젯들을 모두 그려준다.
        SDL_SetRenderTarget(Framework::renderer, nullptr);
        //렌더 타겟을 다시 바꿔준다.
    }
}

void Canvas::render()
{
    if(visibility)
    {
        SDL_Rect dstRect;
        dstRect.x = canvasWorldPosX;
        dstRect.y = canvasWorldPosY;
        dstRect.w = canvasScaleX;
        dstRect.h = canvasScaleY;

        SDL_RenderCopyEx(Framework::renderer, window, NULL, &dstRect,
                         0.0f, NULL, SDL_FLIP_NONE);
        //월드에 그려준다.
    }
}

void Canvas::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_FINGERDOWN)
    {
        testButton->buttonDown();
    }
    else if (e.type == SDL_FINGERMOTION)
    {
    }
    else if (e.type == SDL_FINGERUP)
    {

    }
    //위젯을 순회하며 발생한 이벤트가 있는지 검사하고 적절한 함수를 호출해준다.
}

void Canvas::createEmptyWindow()
{
    window = SDL_CreateTexture(Framework::renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET ,w, h);
    SDL_SetTextureBlendMode(window, SDL_BLENDMODE_BLEND);
}