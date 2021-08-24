#pragma once

#include <vector>
#include <SDL.h>
#include "../Actors/HActor.h"
#include "../Components/CollisionBoxComponent.h"
#include "../HPlayerController.h"

class HLevelBase
{
public:
    HLevelBase() = default;
    virtual ~HLevelBase()
    {
        for(auto&actor : actors)
        {
            delete actor;
            actor = nullptr;
        }
        delete playerController;
        playerController = nullptr;
    }

public:
    virtual void handleEvent(SDL_Event& e) = 0;
    virtual void update(float deltaTime)
    {
        for(auto&actor : actors)
        {
            if(actor)
            {
                actor->update(deltaTime);
            }
        }
        curCollisionCheckTime -= deltaTime;
        if(curCollisionCheckTime <= 0.0f)
        {
            checkingCollision();
            curCollisionCheckTime = maxCollisionCheckTime;
        }
    }
    virtual void render()
    {
        for(auto&actor : actors)
        {
            if(actor)
            {
                actor->render();
            }
        }
    }
    virtual void enter() = 0;
    //이곳에선 레벨 처음 진입시 수행할 작업을 진행한다.
    //enter는 생성자 바디에서 모든 초기화 작업이 수행되고 자동으로 실행되게 코딩한다.
    virtual void exit() = 0;
    //해당 레벨을 떠날 때 (레벨이 바뀔 때) 호출한다.
    template<typename T, typename ...Types>
    T* spawnActor(Types ...args)
    {
        T* newItem = new T(args...);
        addNewActorToLevel(newItem);
        return newItem;
    }

    void addNewActorToLevel(HActor* newActor)
    {
        actors.emplace_back(newActor);
    }
    void addNewCollisionBoxToLevel(CollisionBoxComponent* newBox)
    {
        collisionBoxes.emplace_back(newBox);
    }
    void checkingCollision()
    {
        for(int i = 0; i < collisionBoxes.size() - 1; ++i)
        {
            for(int j = i + 1; j < collisionBoxes.size(); ++j)
            {
                if(collisionBoxes[i]->getOwner()->getVisibility())
                {
                    collisionBoxes[i]->checkCollision(*collisionBoxes[j]);
                }
            }
        }
    }
    const std::vector<HActor*>& getAllActorsInLevel()
    {
        return actors;
    }
    HPlayerController* getPlayerController()
    {
        return playerController;
    }

    void setMaxCollisionCheckingTime(float newTime)
    {
        maxCollisionCheckTime = newTime;
    }
protected:
    std::vector<HActor*> actors;
    std::vector<CollisionBoxComponent*> collisionBoxes;
    HPlayerController* playerController = nullptr;
    float maxCollisionCheckTime = 0.1f;
    float curCollisionCheckTime = 0.1f;
    //추후 이곳에 player controller가 들어가야 한다. (handle event를 위해서)
    //게임모드를 추가할 수도 있고, 아니면 게임모드의 요소를 그냥 멤버로 넣을 수도 있다. (고민좀)
};