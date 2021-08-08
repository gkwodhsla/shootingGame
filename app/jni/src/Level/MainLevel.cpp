#include "MainLevel.h"

#include "../Actors/HActor.h"

MainLevel::MainLevel()
{

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
}

void MainLevel::exit()
{

}