#pragma once

#include <queue>
#include <type_traits>
#include <android/log.h>
#include <functional>
#include "Framework.h"
#include "Level/HLevelBase.h"

template<typename T>
class ActorObjectPool final
{
public:
    ActorObjectPool(size_t chunkSize)
    {
        this->chunkSize = chunkSize;
        if(!std::is_base_of<HActor, T>::value)
        {
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "object pool type must be actor");
            exit(1);
        }
        else
        {
            for(int i = 0; i < chunkSize; ++i)
            {
                if(Framework::curLevel)
                {
                    auto newObj = Framework::curLevel->spawnActor<T>();
                    newObj->setVisibility(false);
                    newObj->setActorTickable(false);
                    //풀에서 새로 만들어진 객체들은 처음엔 visible, tickable하지 않다.
                    objects.push(newObj);
                }
            }
        }
    }

    ActorObjectPool(const ActorObjectPool<T>& src) = delete;
    ActorObjectPool<T>& operator=(const ActorObjectPool<T>&rhs) = delete;

    T* acquireObject()
    {
        if(objects.empty())
        {
            for(int i = 0; i < chunkSize; ++i)
            {
                auto newObj = Framework::curLevel->spawnActor<T>();
                objects.push(newObj);
            }
        }
        auto retObj = objects.front();
        retObj->setVisibility(true);
        retObj->setActorTickable(true);
        objects.pop();
        return retObj;
    }

    void returnToPool(T* obj)
    {
        obj->setVisibility(false);
        obj->setActorTickable(false);
        objects.push(obj);
    }

private:
    std::queue<T*> objects;
    size_t chunkSize = 0;
};
