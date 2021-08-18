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

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> enemyShape(0, 3);

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
        coolTime = 10.0f;
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
                                    BULLET_COLOR::GREEN, Vector2D(0.0f, -1.0f));
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
        int shapeIndex = enemyShape(dre);
        ENEMY_SHIP_SHAPE whichShape = ENEMY_SHIP_SHAPE::SHIP1;
        if(shapeIndex == 0)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP1;
        }
        else if(shapeIndex == 1)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP2;
        }
        else if(shapeIndex == 2)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP3;
        }
        else
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP4;
        }
        auto newEnemy = new EnemyAirplane(BULLET_COLOR::RED, whichShape, 100);
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

//문제가 있음 고쳐야함
void MainLevel::checkingCollision()
{
    for(int i = 0; i < playerBulletSize; ++i)
    {
        if(playerBullets[i]->getVisibility())
        {
            for(int j = 0; j < enemyAirplanes.size(); ++j)
            {
                if(enemyAirplanes[j]->getCanDamaged())
                {
                    bool isHit = playerBullets[i]->getCollisionComp()->checkCollision(*(enemyAirplanes[j]->getCollisionBoxComp()));
                    if(isHit)
                    {
                        enemyAirplanes[j]->getDamage(playerAirplane->getPlayerAttackPower());
                        playerBullets[i]->resetBulletToInitialState();
                        break;
                    }
                }
            }
        }
    }
    //이곳에서 콜리전 검사를 수행한다.
    //1. player bullet과 enemyPlanes
    //2. enemyBullet과 player

}