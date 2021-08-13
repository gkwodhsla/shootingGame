#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../Actors/Airplane.h"
#include "../Actors/Bullet.h"
#include "../Actors/EnemyAirplane.h"
#include "../HPlayerController.h"
#include <vector>

MainLevel::MainLevel()
{
    actors.reserve(300);
    enter();
}

MainLevel::~MainLevel()
{
    exit();
}

void MainLevel::handleEvent(SDL_Event& e)
{
    playerController->handleEvent(e);
}

void MainLevel::update(float deltaTime)
{
    for(auto&actor : actors)
    {
        if(actor)
        {
            actor->update(deltaTime);
        }
    }
}

void MainLevel::render()
{
    for(auto&actor : actors)
    {
        if(actor)
        {
            actor->render();

        }
    }
}

void MainLevel::enter()
{
    BackgroundActor* backgroundActor = new BackgroundActor();
    addNewActorToLevel(backgroundActor);
    playerAirplane = new Airplane();
    addNewActorToLevel(playerAirplane);
    playerController = new HPlayerController();
    playerController->possess(playerAirplane);
    playerBullets.reserve(playerBulletSize);
    for(int i = 0; i < playerBulletSize; ++i)
    {
        auto newBullet = new Bullet(std::make_pair(0.0f, 0.0f),
                                    BULLET_COLOR::GREEN, std::make_pair(0.0f,-1.0f));
        playerBullets.push_back(newBullet);
        playerBullets[i]->setVisibility(false);
        playerBullets[i]->setActorTickable(false);
        playerBullets[i]->setIsSetLifeTime(true);
        addNewActorToLevel(newBullet);
    }
    enemyTemp = new EnemyAirplane(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::SHIP4, 100);
    addNewActorToLevel(enemyTemp);
}

void MainLevel::exit()
{
    for(auto&actor : actors)
    {
        delete actor;
        actor = nullptr;
    }
    delete playerController;
    playerController = nullptr;

    delete enemyTemp;
    enemyTemp = nullptr;
}