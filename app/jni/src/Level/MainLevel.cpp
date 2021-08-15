#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../Actors/Airplane.h"
#include "../Actors/Bullet.h"
#include "../Actors/EnemyAirplane.h"
#include "../HPlayerController.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SplineComponent.h"
#include "../Actors/Spawner.h"
#include <vector>
#include <android/log.h>

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
    checkingCollision();

    //일단 임의로 적을 스폰해보자!
    coolTime -= deltaTime;
    if(coolTime <= 0)
    {
        spawner->startSpawn(1);
        coolTime = 3.0f;
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

    int enemySize = Spawner::numOfDestX * Spawner::numOfDestY;
    enemyAirplanes.reserve(enemySize);
    for(int i = 0; i < enemySize;++i)
    {
        auto newEnemy = new EnemyAirplane(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::SHIP1, 100);
        newEnemy->setVisibility(false);
        newEnemy->setActorTickable(false);
        enemyAirplanes.push_back(newEnemy);
        addNewActorToLevel(newEnemy);
    }

    spawner = new Spawner();
    addNewActorToLevel(spawner);
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

    delete spawner;
    spawner = nullptr;
}

void MainLevel::checkingCollision()
{
    for(int i = 0; i < playerBulletSize; ++i)
    {
        if(playerBullets[i]->getVisibility())
        {
            for(int j = 0; j < enemyAirplanes.size();++j)
            {
                if(enemyAirplanes[i]->getVisibility())
                {
                    bool isHit = playerBullets[i]->getCollisionComp()->checkCollision(*(enemyAirplanes[i]->getCollisionBoxComp()));
                    if(isHit)
                    {
                        enemyAirplanes[i]->getDamage(playerAirplane->getPlayerAttackPower());
                        playerBullets[i]->resetBulletToInitialState();
                        break;
                    }
                }
            }
            //if(isHit) //히트됐다면
            //{
            //    playerBullets[i]->resetBulletToInitialState(); //총알을 버퍼에 돌려준다.
                //적에게 데미지를 입힌다.
            //}
        }
    }
    //이곳에서 콜리전 검사를 수행한다.
    //1. player bullet과 enemyPlanes
    //2. enemyBullet과 player

}