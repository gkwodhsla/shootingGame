#pragma once

#include "HLevelBase.h"

class MainLevel: public HLevelBase
{
public:
    MainLevel();
    virtual ~MainLevel();
    void handleEvent() override;
    void update(float deltaTime) override;
    void render() override;
    void enter() override;
    void exit() override;
};