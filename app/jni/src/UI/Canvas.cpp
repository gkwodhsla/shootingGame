#include "Canvas.h"
#include "../Framework.h"
#include "Widget.h"
#include "ButtonWidget.h"

Canvas::Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY):
w(canvasW), h(canvasH), canvasWorldPosX(canvasWorldX), canvasWorldPosY(canvasWorldY)
{
    createEmptyWindow();
    Framework::worldUI.push_back(this);
}

Canvas::~Canvas()
{
    SDL_DestroyTexture(window);
    window = nullptr;

    for(auto& widget : canvasWidgets)
    {
        delete widget;
        widget = nullptr;
    }
}

void Canvas::addToViewport()
{
    visibility = true;
}

void Canvas::removeFromViewport()
{
    visibility = false;
}

void Canvas::addWidgetToBuffer(Widget* newWidget)
{
    canvasWidgets.push_back(newWidget);
}

void Canvas::addButtonToBuffer(ButtonWidget* newWidget)
{
    canvasButtons.push_back(newWidget);
}

void Canvas::canvasRender()
{
    if(visibility)
    {
        SDL_SetRenderTarget(Framework::renderer, window);
        SDL_SetRenderDrawColor(Framework::renderer, 0xff, 0xff, 0xff, 0);
        SDL_RenderClear(Framework::renderer);
        for(auto& widget : canvasWidgets)
        {
            if(widget->getVisibility())
            {
                widget->render();
            }
        }
        SDL_SetRenderTarget(Framework::renderer, nullptr);
    }
}

void Canvas::render()
{
    if(visibility)
    {
        SDL_Rect dstRect;
        dstRect.x = canvasWorldPosX;
        dstRect.y = canvasWorldPosY;
        dstRect.w = w;
        dstRect.h = h;

        SDL_RenderCopyEx(Framework::renderer, window, NULL, &dstRect,
                         0.0f, NULL, SDL_FLIP_NONE);
        //월드에 그려준다.
    }
}

bool Canvas::handleEvent(SDL_Event &e)
{
    bool isEventOccure = false;
    if(visibility)
    {
        int x = int(e.tfinger.x * float(Framework::rendererWidth));
        int y = int(e.tfinger.y * float(Framework::rendererHeight));
        if (e.type == SDL_FINGERDOWN)
        {
            for(auto& button : canvasButtons)
            {
                if(!isEventOccure)
                {
                    isEventOccure = button->checkIsClicked(x, y);
                }
                else
                {
                    button->checkIsClicked(x, y);
                }
            }
        }
        else if (e.type == SDL_FINGERMOTION) //버튼의 hovering을 검사한다.
        {
            for(auto& button : canvasButtons)
            {
                if(!isEventOccure)
                {
                    isEventOccure = button->checkIsHovering(x, y);
                }
                else
                {
                    button->checkIsHovering(x, y);
                }
            }
        }
        else if (e.type == SDL_FINGERUP)
        {
            for(auto& button : canvasButtons)
            {
                if(!isEventOccure)
                {
                    isEventOccure = button->checkIsClicked(x, y);
                }
                else
                {
                    button->checkIsClicked(x, y);
                }
            }
            for(auto& button : canvasButtons)
            {
                button->setButtonUp();
            }
        }
    }
    return isEventOccure;
}

void Canvas::changeWindowAlphaValue(__uint8_t alpha)
{
    SDL_SetTextureAlphaMod(window, alpha);
}

void Canvas::createEmptyWindow()
{
    window = SDL_CreateTexture(Framework::renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET ,w, h);
    SDL_SetTextureBlendMode(window, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(window, 255);
}