#pragma once

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
    void possess(HPawn* pawn);
    void changeInputMode(INPUT_MODE inputMode);
    void handleEvent();
    HPawn* getControlledPawn();
private:
    HPawn* controlledPawn = nullptr;
    INPUT_MODE curInputMode = INPUT_MODE::GAME_ONLY;
};


