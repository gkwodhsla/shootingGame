#pragma once
#include <type_traits>

class HLevelBase;
class HPlayerController;
class HPawn;

namespace GlobalFunction
{
    template<typename To, typename From>
    To* Cast(From* src) //안전한 다운캐스팅을 지원하는 함수이다.
    {
        if(!std::is_base_of<From, To>::value) //만약 From이 To의 부모 클래스가 아니면 캐스팅은 실패!
        {
            return nullptr;
        }
        else
        {
            return dynamic_cast<To*>(src);
        }
    }
    HLevelBase* GetLevel();

    HPlayerController* GetPlayerController();

    HPawn* GetPlayerPawn();
}