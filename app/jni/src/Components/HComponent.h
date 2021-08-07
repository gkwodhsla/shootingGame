#pragma once

#include <string>

//class HActor;

class HComponent
{
public:
    HComponent() = default;
    virtual ~HComponent() = default;

public:
    virtual void update(float deltaTime) = 0;
    //HActor* getOwner()
    //{
        //return owner;
    //}

public:
    void setComponentTickable(bool isTickable)
    {
        tickable = isTickable;
    }
    bool getComponentTickable()
    {
        return tickable;
    }
    std::string getComponentTag()
    {
        return componentTag;
    }

protected:
    //HActor* owner;
    std::string componentTag;
    bool tickable;
};
