#include "SpritesheetComponent.h"
#include "../Framework.h"
#include <vector>
#include <functional>
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

void SpritesheetComponent::update(const float deltaTime)
{
    HPrimitiveComponent::update(deltaTime);
    if(visibility)
    {
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
        if(int(curFrame) % clipRects.size() != befFrame)
        {
            if(events.find(int(curFrame) % clipRects.size()) != events.end()) //이벤트가 등록되어있는 경우만 호출해준다.
            {
                events[int(curFrame) % clipRects.size()]();
            }
        }
        befFrame = int(curFrame) % clipRects.size();
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
    befFrame = -1;
    visibility = false;
}

void SpritesheetComponent::addEventAtNFrame(int n, const std::function<void()>& func)
{
    events.insert({n, func});
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