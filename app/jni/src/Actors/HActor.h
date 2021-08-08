#pragma once

#include <utility>

class HSceneComponent;
class SDL_Renderer;

class HActor
{
public:
    HActor();
    virtual ~HActor();

public:
    void moveTo(const std::pair<int, int>& loc);
    void rotateActor(float degree);
    void render();
    virtual void update();

public:
    void setVisibility(bool isVisible);
    const bool getVisibility();
    const HSceneComponent* getRootComponent;
    void setRootComponent(HSceneComponent* component);
    const std::pair<int, int> getActorDirectionalVector();
    const std::pair<int, int> getActorWorldLocation();
    const float getActorWorldRotation();
    void setActorTickable(bool isTickable);
    const bool getActorTickable();

protected:
    HSceneComponent* rootComponent;
    std::pair<float, float> dirVec;
    bool visibility;
    bool tickable;
    //추후 HActorComponent 구현 시 넣어야함
    //HActor는 따로 관리해야함 (vector 사용 예정)
};
