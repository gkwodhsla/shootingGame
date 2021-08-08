#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"

MainLevel::MainLevel()
{
    enter();
}

MainLevel::~MainLevel()
{

}

void MainLevel::handleEvent()
{

}

void MainLevel::update(float deltaTime)
{
    for(auto&actor : actors)
    {
        actor->update(deltaTime);
    }
}

void MainLevel::render()
{
    for(auto&actor : actors)
    {
        actor->render();
    }
}

void MainLevel::enter()
{
    BackgroundActor* backgroundActor = new BackgroundActor();
    addNewActorToLevel(backgroundActor);
}

void MainLevel::exit()
{
    for(auto&actor : actors)
    {
        delete actor;
        actor = nullptr;
    }
}