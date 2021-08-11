#pragma once

#include "HActor.h"
#include <SDL.h>

class MovementComponent;
class HPlayerController;

class HPawn :public HActor
{
public:
    HPawn();
    virtual ~HPawn();
    void setCanRecvInputEvent(bool canInput);
    HPlayerController* getController();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) = 0;
private:
    MovementComponent* movementComp = nullptr;
    HPlayerController* controller = nullptr;
    bool canReceiveInputFromPlayer = true;
};