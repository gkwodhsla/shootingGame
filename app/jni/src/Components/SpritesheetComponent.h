#pragma once

#include "ImageComponent.h"
#include <map>

class SpritesheetComponent : public ImageComponent
{
public:
    SpritesheetComponent() = default;
    SpritesheetComponent(const std::string& path, const std::pair<int, int>& loc, HActor* owner, int imgCnt,
                         int rowCnt, int colCnt);
    virtual ~SpritesheetComponent();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    void play();
    void stop();
    void addEventAtNFrame(int n, const std::function<void()>& func);
public:
    void setLooping(bool isLooping);
    const bool getLooping();
    void setDrawCntPerSec(int cnt);
    bool getIsPlayEnd();

private:
    std::vector<SDL_Rect*> clipRects;
    std::map<int, std::function<void()>> events;
    bool isLooping = false;
    bool canIncFrame = false;
    bool isPlayEnd = false;
    float curFrame = 0;
    int befFrame = -1;
    int drawCntPerSec = 10;
};

