#pragma once
#include <type_traits>
#include <typeinfo>
#include <android/log.h>
#include <random>

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
    HLevelBase* GetLevel();

    HPlayerController* GetPlayerController();

    HPawn* GetPlayerPawn();
}