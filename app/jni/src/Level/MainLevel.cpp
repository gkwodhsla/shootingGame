#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../Actors/Airplane.h"
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
    /*coolTime -= deltaTime;
    if(coolTime <= 0)
    {
        spawner->startSpawn(1);
        coolTime = 10.0f;
    }*/
    if(!isBossSpawned)
    {
        spawner->spawnBoss(1);
        isBossSpawned = true;
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
        addBulletToBuffer(playerBullets, BULLET_COLOR::GREEN);
    }

    enemyRedBullets.reserve(enemyBulletSize);
    enemyPurpleBullets.reserve(enemyBulletSize);
    enemyBlueBullets.reserve(enemyBulletSize);
    enemySkyBullets.reserve(enemyBulletSize);

    for(int i = 0; i < enemyBulletSize; ++i)
    {
        addBulletToBuffer(enemyRedBullets, BULLET_COLOR::RED);
        addBulletToBuffer(enemyBlueBullets, BULLET_COLOR::BLUE);
        addBulletToBuffer(enemySkyBullets, BULLET_COLOR::SKY);
        addBulletToBuffer(enemyPurpleBullets, BULLET_COLOR::PURPLE);
    }

    int enemySize = Spawner::numOfDestX * Spawner::numOfDestY;
    enemyAirplanes.reserve(enemySize);
    for(int i = 0; i < enemySize;++i)
    {
        int shapeIndex = enemyShape(dre);
        ENEMY_SHIP_SHAPE whichShape = ENEMY_SHIP_SHAPE::SHIP1;
        BULLET_COLOR enemyBulletColor = BULLET_COLOR::RED;
        if(shapeIndex == 0)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP1;
            enemyBulletColor = BULLET_COLOR::RED;
        }
        else if(shapeIndex == 1)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP2;
            enemyBulletColor = BULLET_COLOR::BLUE;
        }
        else if(shapeIndex == 2)
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP3;
            enemyBulletColor = BULLET_COLOR::SKY;
        }
        else
        {
            whichShape = ENEMY_SHIP_SHAPE::SHIP4;
            enemyBulletColor = BULLET_COLOR::PURPLE;
        }
        auto newEnemy = new EnemyAirplane(enemyBulletColor, whichShape, 100);
        newEnemy->setVisibility(false);
        newEnemy->setActorTickable(false);
        enemyAirplanes.push_back(newEnemy);
        addNewActorToLevel(newEnemy);
    }

    boss1 = new EnemyAirplane(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::BOSS1, 100);
    boss1->setVisibility(false);
    boss1->setActorTickable(false);
    boss1->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_CIRCLE);
    addNewActorToLevel(boss1);

    boss2 = new EnemyAirplane(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::BOSS2, 100);
    boss2->setVisibility(false);
    boss2->setActorTickable(false);
    boss2->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_CIRCLE);
    addNewActorToLevel(boss2);

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
}

//문제가 있음 고쳐야함
void MainLevel::checkingCollision()
{
    for(int i = 0; i < playerBulletSize; ++i)
    {
        if(playerBullets[i]->getVisibility())
        {
            if(isBossSpawned && boss1->getCanDamaged())
            {
                bool isHit = playerBullets[i]->getCollisionComp()->checkCollision(*(boss1->getCollisionBoxComp()));
                if(isHit)
                {
                    boss1->getDamage(playerAirplane->getPlayerAttackPower());
                    playerBullets[i]->resetBulletToInitialState();
                }
            }

            else if(isBossSpawned && boss2->getCanDamaged())
            {
                bool isHit = playerBullets[i]->getCollisionComp()->checkCollision(*(boss2->getCollisionBoxComp()));
                if(isHit)
                {
                    boss2->getDamage(playerAirplane->getPlayerAttackPower());
                    playerBullets[i]->resetBulletToInitialState();
                }
            }

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

void MainLevel::addBulletToBuffer(std::vector<Bullet*>& cont, BULLET_COLOR color)
{
    auto newBullet = new Bullet(std::make_pair(0.0f, 0.0f),
                                color, Vector2D(0.0f, -1.0f));
    newBullet->setVisibility(false);
    newBullet->setActorTickable(false);
    newBullet->setIsSetLifeTime(true);
    cont.push_back(newBullet);
    addNewActorToLevel(newBullet);
}