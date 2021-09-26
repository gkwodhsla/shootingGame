#pragma once

#include <vector>
#include <SDL.h>
#include <algorithm>
#include "../Actors/HActor.h"
#include "../Components/CollisionBoxComponent.h"
#include "../HPlayerController.h"
#include "../UI/Canvas.h"
#include "../Framework.h"
#include "../GlobalFunction.h"
#include "../HObject.h"
//액터가 배치되는 게임 월드이다.
class HLevelBase: public HObject
{
public:
    HLevelBase() = default;
    HLevelBase(const HLevelBase&) = delete;
    HLevelBase& operator=(const HLevelBase&) = delete;
    virtual ~HLevelBase()
    {
        for(auto&actor : actors)
        {
            if(actor)
            {
                delete actor;
                actor = nullptr;
            }
        }

        for(auto&box : collisionBoxes) //충돌박스 컴포넌트는 액터의 소멸에 따라 자연스럽게 사라지지만 만약을 위해 지우는 코드를 추가함
        {
            if(box)
            {
                delete box;
                box = nullptr;
            }
        }
        delete playerController;
        playerController = nullptr;
    }

public:
    virtual void handleEvent(const SDL_Event& e)
    {
        if(playerController)
        {
            INPUT_MODE curInputMode = playerController->getInputMode();
            switch(curInputMode)
            {
                case INPUT_MODE::GAME_ONLY:
                    playerController->handleEvent(e);
                    break;
                case INPUT_MODE::UI_ONLY:
                    for(auto& canvas : Framework::worldUI)
                    {
                        canvas->handleEvent(e);
                    }
                    break;
                case INPUT_MODE::BOTH:
                    for(auto& canvas : Framework::worldUI)
                    {
                        canvas->handleEvent(e);
                    }
                    playerController->handleEvent(e);
                    break;
            }
        }
    }
    virtual void update(const float deltaTime)
    {
        eraseMakredActor(deltaTime);

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
    virtual void exit() = 0;
    //해당 레벨을 떠날 때 (레벨이 바뀔 때) 호출한다.
    template<typename T, typename ...Types>
    T* spawnActor(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);
        addNewActorToLevel(newItem);
        return newItem;
    }
    //액터를 생성하고 액터 배열에 집어넣어 업데이트와 렌더링이 수행되게 해준다.


    bool destroyActor(HActor* actor)
    {
        bool isDestroyed = false;
        for(int i = 0; i < actors.size(); ++i)
        {
            if(actor == actors[i])
            {
                actor->setVisibility(false);
                actor->setActorTickable(false);
                actor->setPendingKill(true);
                actor = nullptr;
                isDestroyed = true;
                break;
            }
        }
        return isDestroyed;
    }
    //마킹만 해두고 실제 제거 작업은 뒤로 미룬다.

    bool destroyBox(CollisionBoxComponent* box)
    {
        bool isSuccess = false;
        for(int i = 0; i < collisionBoxes.size(); ++i)
        {
            if(box == collisionBoxes[i])
            {
                collisionBoxes[i] = nullptr;
                isSuccess = true;
                break;
            }
        }
        return isSuccess;
    }
    //액터 파괴시 콜리전박스가 파괴되는데 박스의 소멸자에서 이 함수를 호출해 박스를 관리하는
    //배열에서도 null이 되게끔 해준다.

    void addNewActorToLevel(HActor* newActor)
    {
        actors.emplace_back(newActor);
    }
    void addNewCollisionBoxToLevel(CollisionBoxComponent* newBox)
    {
        collisionBoxes.emplace_back(newBox);
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

    void setClearGarbageTime(float newTime)
    {
        maxEraseBufferTime = newTime;
    }

private:
    void checkingCollision()
    {
        for(int i = 0; i < int(collisionBoxes.size()) - 1; ++i)
        {
            for(int j = i + 1; j < collisionBoxes.size(); ++j)
            {
                if(collisionBoxes[i] && collisionBoxes[j])
                {
                    if(collisionBoxes[i]->getOwner()->getVisibility() &&
                       collisionBoxes[j]->getOwner()->getVisibility())
                    {
                        collisionBoxes[i]->checkCollision(*collisionBoxes[j]);
                    }
                }
            }
        }
    }
    //레벨에 렌더링되고 있는 액터들을 대상으로 충돌검사를 수행한다.

    void eraseMakredActor(float deltaTime)
    {
        curEraseBufferTime -= deltaTime;
        if (curEraseBufferTime <= 0.0f)
        {
            for(auto&actor: actors)
            {
                if(actor->getPendingKill())
                {
                    delete actor;
                    actor = nullptr;
                }
            }
            auto actorIter = std::remove(std::begin(actors), std::end(actors),nullptr);
            actors.erase(actorIter, std::end(actors));

            auto boxIter = std::remove(std::begin(collisionBoxes), std::end(collisionBoxes),nullptr);
            collisionBoxes.erase(boxIter, std::end(collisionBoxes));

            curEraseBufferTime = maxEraseBufferTime;
        }
    }
    //할당해제 되어 액터 배열에서 null인 요소들을 제거한다.
    //할당해제 되어 콜리전 박스 배열에서 null인 요소들을 제거한다.

protected:
    std::vector<HActor*> actors;
    std::vector<CollisionBoxComponent*> collisionBoxes;
    HPlayerController* playerController = nullptr;
    float maxCollisionCheckTime = 0.02f;
    float curCollisionCheckTime = 0.02f;
    float maxEraseBufferTime = 10.0f;
    float curEraseBufferTime = 10.0f;
};