#pragma once

class HObject
{
public:
    HObject() = default;
    virtual ~HObject() = 0;
    void setID(void* newID)
    {
        id = newID;
    }
    void* getID()
    {
        return id;
    }

public:
    void* id = nullptr;
};