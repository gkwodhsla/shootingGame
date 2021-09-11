#pragma once

#include <string>
#include "../Actors/HActor.h"
#include "../HObject.h"

class HComponent: public HObject
{
public:
    HComponent() = default;
    HComponent(const HComponent&) = delete;
    HComponent& operator=(const HComponent&) = delete;
    virtual ~HComponent() = default;

public:
    virtual void update(const float deltaTime) = 0;
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
