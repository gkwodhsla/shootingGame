#include "Canvas.h"
#include "../Framework.h"
#include <SDL.h>


Canvas::Canvas(int canvasW, int canvasH, int canvasWorldX, int canvasWorldY):
w(canvasW), h(canvasH), canvasWorldPosX(canvasWorldX), canvasWorldPosY(canvasWorldY)
{
    createEmptyWindow();
    //Framework::worldUI.push_back(this);
    canvasXRatio = float(RTWidth) / float(canvasW);
    canvasYRatio = float(RTHeight) / float(canvasH);
    canvasInterpolate = (float(RTWidth)/float(RTHeight))*(float(canvasH)/float(canvasW));

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

void Canvas::addEditBoxToBuffer(EditBoxWidget* newWidget)
{
    editBoxes.push_back(newWidget);
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

bool Canvas::handleEvent(const SDL_Event &e)
{
    bool isEventOccure = false;
    if(visibility)
    {
        int x = int(e.tfinger.x * float(Framework::rendererWidth)) - canvasWorldPosX;
        x = int(float(x) * canvasXRatio);
        int y = int(e.tfinger.y * float(Framework::rendererHeight)) - canvasWorldPosY;
        y = int(float(y) * canvasYRatio);
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
            bool isClicked = false;
            for(auto& box : editBoxes)
            {
                if(box->checkIsClicked(x, y))
                {
                    box->setIsFocused(true);
                    box->swapText();
                    isClicked = true;
                }
                else
                {
                    box->setIsFocused(false);
                    box->swapText();
                }
            }

            if(isClicked)
            {
                SDL_StartTextInput();
            }
            else
            {
                SDL_StopTextInput();
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
        else if(e.type == SDL_TEXTINPUT)
        {
            for(auto&box: editBoxes)
            {
                if(box->getIsFocused())
                {
                    box->addContent(e.text.text);
                }
            }
        }
        else if(e.type == SDL_TEXTEDITING)
        {

        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_BACKSPACE:
                    for(auto&box: editBoxes)
                    {
                        if(box->getIsFocused())
                        {
                            box->eraseContent();
                        }
                    }
                    break;
            }
        }
    }
    return isEventOccure;
}

void Canvas::update(const float deltaTime)
{
    if(visibility)
    {
        for(auto& widget : canvasWidgets)
        {
            widget->update(deltaTime);
        }
    }
}

void Canvas::changeWindowAlphaValue(__uint8_t alpha)
{
    SDL_SetTextureAlphaMod(window, alpha);
}

void Canvas::createEmptyWindow()
{
    //렌더타겟의 크기는 1080x1704로 고정. 폰의 렌더러의 크기에 따라 조정되게끔 해준다.
    window = SDL_CreateTexture(Framework::renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET ,RTWidth, RTHeight);
    SDL_SetTextureBlendMode(window, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(window, 255);
}

float Canvas::getCanvasXRatio() const
{
    return canvasXRatio;
}

float Canvas::getCanvasYRatio() const
{
    return canvasYRatio;
}

float Canvas::getCanvasInterpValue()const
{
    return canvasInterpolate;
}