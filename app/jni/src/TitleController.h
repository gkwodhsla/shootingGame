#pragma once

#include "HPlayerController.h"

class LoginCanvas;

class TitleController: public HPlayerController
{
public:
    TitleController(HPawn* controlledPawn);
    TitleController(const TitleController&) = delete;
    TitleController& operator=(const TitleController&) = delete;
    virtual ~TitleController();
    void goToMainLevel();
private:
    LoginCanvas* loginCanvas = nullptr;
};


