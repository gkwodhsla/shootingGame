#pragma once

#include <vector>

class HActor;

class HLevelBase
{
public:
    HLevelBase() = default;
    virtual ~HLevelBase() = default;

public:
    virtual void handleEvent() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void enter() = 0;
    //이곳에선 레벨 처음 진입시 수행할 작업을 진행한다.
    //enter는 생성자 바디에서 모든 초기화 작업이 수행되고 자동으로 실행되게 코딩한다.
    virtual void exit() = 0;
    //해당 레벨을 떠날 때 (레벨이 바뀔 때) 호출한다.
    //동적할당 받은 객체들을 초기화 해준다.
    void addNewActorToLevel(HActor* newActor)
    {
        actors.emplace_back(newActor);
    }
    const std::vector<HActor*>& getAllActorsInLevel()
    {
        return actors;
    }

protected:
    std::vector<HActor*> actors;
    //추후 이곳에 player controller가 들어가야 한다. (handle event를 위해서)
    //게임모드를 추가할 수도 있고, 아니면 게임모드의 요소를 그냥 멤버로 넣을 수도 있다. (고민좀)
};