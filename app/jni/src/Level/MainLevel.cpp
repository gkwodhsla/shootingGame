#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../HPlayerController.h"

MainLevel::MainLevel()
{
    enter();
    playerController = new HPlayerController();
}

MainLevel::~MainLevel()
{

}

void MainLevel::handleEvent(SDL_Event& e)
{
    playerController->handleEvent(e);
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