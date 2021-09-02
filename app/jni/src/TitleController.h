#pragma once

#include "HPlayerController.h"

class LoginCanvas;

class TitleController: public HPlayerController
{
public:
    TitleController(HPawn* controlledPawn);
    virtual ~TitleController();
    void goToMainLevel();
private:
    LoginCanvas* loginCanvas = nullptr;
};


