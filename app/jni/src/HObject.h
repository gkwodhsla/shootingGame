#pragma once

class HObject
{
public:
    HObject() = default;
    HObject(const HObject&) = delete;
    HObject& operator=(const HObject&) = delete;
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