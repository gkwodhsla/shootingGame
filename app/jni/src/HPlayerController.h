#pragma once

#include <SDL.h>
#include "HObject.h"

class HPawn;

enum class INPUT_MODE
{
    UI_ONLY,
    GAME_ONLY,
    BOTH
};

class HPlayerController: public HObject
{
public:
    HPlayerController(HPawn* controlledPawn);
    virtual ~HPlayerController();
    void possess(HPawn* pawn);
    void unpossess();
    void changeInputMode(const INPUT_MODE inputMode);
    INPUT_MODE getInputMode();
    void handleEvent(SDL_Event& e);
    HPawn* getControlledPawn();

protected:
    HPawn* controlledPawn = nullptr;
    INPUT_MODE curInputMode = INPUT_MODE::GAME_ONLY;
};


