#pragma once

#include "HLevelBase.h"

class TitleLevel : public HLevelBase
{
public:
    TitleLevel();
    virtual ~TitleLevel();
    virtual void handleEvent(const SDL_Event& e) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void enter() override;
    virtual void exit() override;
};

