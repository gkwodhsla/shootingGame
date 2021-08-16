#include "SpritesheetComponent.h"
#include "../Framework.h"
#include <vector>
#include <SDL.h>
#include <android/log.h>

SpritesheetComponent::SpritesheetComponent(const std::string &path, const std::pair<int, int> &loc,
                                           HActor *owner, int imgCnt, int rowCnt, int colCnt)
                                           : ImageComponent(path, loc, owner)
{
    clipRects.reserve(imgCnt);
    int yCnt = -1;

    float imgWidth = float(imgRect->w) / float(rowCnt);
    float imgHeight = float(imgRect->h) / float(colCnt);

    for(int i = 0; i < imgCnt; ++i)
    {
        auto newClipRect = new SDL_Rect();
        if(i % rowCnt == 0)
        {
            ++yCnt;
        }
        newClipRect->x = int((i % rowCnt) * imgWidth);
        newClipRect->y = int(yCnt * imgHeight);
        newClipRect->w = int(imgWidth);
        newClipRect->h = int(imgHeight);

        clipRects.push_back(newClipRect);
    }
    visibility = false;
}

SpritesheetComponent::~SpritesheetComponent()
{
    for(int i = 0; i < clipRects.size(); ++i)
    {
        delete clipRects[i];
        clipRects[i] = nullptr;
    }
}

void SpritesheetComponent::render()
{
    HPrimitiveComponent::render();

    if(visibility)
    {
        SDL_Rect dstRect;
        dstRect.x = int(worldLocation.first);
        dstRect.y = int(worldLocation.second);
        dstRect.w = scale.first;
        dstRect.h = scale.second;

        SDL_RenderCopyEx(Framework::renderer, img, clipRects[int(curFrame) % clipRects.size()],
                         &dstRect,
                         localRotation, NULL, flip);
    }
}

void SpritesheetComponent::update(float deltaTime)
{
    HPrimitiveComponent::update(deltaTime);
    if(!isLooping)
    {
        if(curFrame > clipRects.size() - 1)
        {
            stop();
        }
    }
    if(canIncFrame)
    {
        curFrame +=  drawCntPerSec * deltaTime;
    }
}

void SpritesheetComponent::play()
{
    canIncFrame = true;
    visibility = true;
    isPlayEnd = false;
}

void SpritesheetComponent::stop()
{
    canIncFrame = false;
    isPlayEnd = true;
    curFrame = 0;
    visibility = false;
}

void SpritesheetComponent::setLooping(bool isLooping)
{
    this->isLooping = isLooping;
}

const bool SpritesheetComponent::getLooping()
{
    return isLooping;
}

void SpritesheetComponent::setDrawCntPerSec(int cnt)
{
    drawCntPerSec = cnt;
}

bool SpritesheetComponent::getIsPlayEnd()
{
    return isPlayEnd;
}