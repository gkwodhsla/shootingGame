#pragma once

#include <string>
#include "../Actors/HActor.h"

class HComponent
{
public:
    HComponent() = default;
    virtual ~HComponent() = default;

public:
    virtual void update(float deltaTime) = 0;
    HActor* getOwner()
    {
        return owner;
    }

public:
    void setComponentTickable(bool isTickable)
    {
        tickable = isTickable;
    }
    const bool getComponentTickable()
    {
        return tickable;
    }
    const std::string getComponentTag()
    {
        return componentTag;
    }

protected:
    HActor* owner;
    std::string componentTag;
    bool tickable = true;
};
