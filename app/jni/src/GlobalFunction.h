#pragma once
#include <type_traits>
#include <typeinfo>
#include <android/log.h>
#include <random>
#include "Framework.h"

class HLevelBase;
class HPlayerController;
class HPawn;

extern std::random_device rd;
extern std::default_random_engine dre;
extern std::uniform_real_distribution<float> randomRot;

namespace GlobalFunction
{
    template<typename T>
    void* GetClassTypeUniqueID()
    {
        static int a = 0;
        return &a;
    }
    //타입을 입력받아 해당 타입의 고유 ID를 반환한다.

    template<typename To, typename From>
    To* Cast(From* src) //안전한 다운캐스팅을 지원하는 함수이다.
    {
        if(GetClassTypeUniqueID<To>() == src->getID())
        {
            return (To*)src;
        }
        else
        {
            if(src->getID() == nullptr)
            {
                __android_log_print(ANDROID_LOG_INFO, "Cast_Error",
                                    "Warning: Input Class %s has no unique ID Please Set Unique ID"
                                    " using setID(GlobalFunction::<ClassType>GetClassTypeUniqueID())", typeid(From).name());
            }
            return nullptr;
        }
    }

    template<typename T, typename ...Types>
    static T* createNewObject(Types ...args)
    {
        T* newItem = new T(args...);
        newItem->setID(GlobalFunction::GetClassTypeUniqueID<T>());
        return newItem;
    }
    //Actor, Component, Canvas, Widget을 제외한 객체를 생성할 때 사용하는 함수이다.
    //생성하고자 하는 객체는 반드시 부모로 HObject를 상속받아야한다.

    template<typename T, typename ...Types>
    static T* makeCanvas(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);
        Framework::worldUI.push_back(newItem);
        return newItem;
    }
    //캔버스를 생성하는 함수이다.

    HLevelBase* GetLevel();

    HPlayerController* GetPlayerController();

    HPawn* GetPlayerPawn();
}