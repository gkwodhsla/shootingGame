#pragma once

#include "HActor.h"
class BackgroundActor :public HActor
{
public:
    BackgroundActor();
    virtual ~BackgroundActor();

public:
    void render();
    void update();
};