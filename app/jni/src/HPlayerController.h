#pragma once

#include <SDL.h>
class HPawn;

enum class INPUT_MODE
{
    UI_ONLY,
    GAME_ONLY
};

class HPlayerController
{
public:
    HPlayerController();
    virtual ~HPlayerController();
    void possess(const HPawn* pawn);
    void unpossess();
    void changeInputMode(const INPUT_MODE inputMode);
    void handleEvent(SDL_Event& e);
    HPawn* getControlledPawn();

protected:
    HPawn* controlledPawn = nullptr;
    INPUT_MODE curInputMode = INPUT_MODE::GAME_ONLY;
};


