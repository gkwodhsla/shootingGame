#pragma once

#include "HActor.h"

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
    virtual void handleEvent();
private:
    MovementComponent* movementComp = nullptr;
    HPlayerController* controller = nullptr;
    bool canReceiveInputFromPlayer = true;
};