#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../Actors/Airplane.h"
#include "../Actors/EnemyAirplane.h"
#include "../HPlayerController.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SplineComponent.h"
#include "../Actors/Spawner.h"
#include "../Actors/StageManager.h"
#include "../UI/ShopCanvas.h"
#include "../UI/InGameCanvas.h"
#include "../Framework.h"
#include "../ActorObjectPool.h"
#include "../GlobalFunction.h"
#include <vector>
#include <android/log.h>

using namespace GlobalFunction;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> enemyShape(0, 3);

MainLevel::MainLevel()
{
    actors.reserve(300);
    collisionBoxes.reserve(500);
}

MainLevel::~MainLevel()
{
}

void MainLevel::handleEvent(SDL_Event& e)
{
    INPUT_MODE curInputMode = playerController->getInputMode();
    if(curInputMode == INPUT_MODE::GAME_ONLY)
    {
        playerController->handleEvent(e);
    }
    else if (curInputMode == INPUT_MODE::UI_ONLY)
    {
        for(auto& canvas : Framework::worldUI)
        {
            canvas->handleEvent(e);
        }
    }
    else if(curInputMode == INPUT_MODE::BOTH)
    {
        bool isUserInteractWithUI = false;
        for(auto& canvas : Framework::worldUI)
        {
            if (!isUserInteractWithUI)
            {
                isUserInteractWithUI = canvas->handleEvent(e);
            }
            else
            {
                canvas->handleEvent(e);
            }
        }
        if(!isUserInteractWithUI)
        {
            playerController->handleEvent(e);
        }
    }
}

void MainLevel::update(float deltaTime)
{
    HLevelBase::update(deltaTime);

    ShopCanvas* curCanvas = Cast<ShopCanvas>(shopCanvas);


    if(curCanvas->getIsPlayButtonClicked())
    {
        playerAirplane->playerInitWhenStageBegin();
        curCanvas->removeFromViewport();
        curCanvas->setIsPlayButtonClicked(false);
        playerController->changeInputMode(INPUT_MODE::BOTH);
        stageManager->setStage(curCanvas->getCurStage());
        stageManager->waveBegin();
        inGameCanvas->addToViewport();
    }

    if(isClear)
    {
        coolTime -= deltaTime;
        if(coolTime<=0.0f)
        {
            afterStageClear();
        }
    }
}

void MainLevel::render()
{
    HLevelBase::render();
}

void MainLevel::enter()
{
    spawnActor<BackgroundActor>();
    stageManager = spawnActor<StageManager>();
    playerAirplane = spawnActor<Airplane>();
    playerAirplane->setVisibility(false);
    playerAirplane->setActorTickable(false);

    playerController = new HPlayerController();
    playerController->possess(playerAirplane);
    playerController->changeInputMode(INPUT_MODE::UI_ONLY);

    int enemySize = 16;//Spawner::numOfDestX * Spawner::numOfDestY;
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
        auto newEnemy = spawnActor<EnemyAirplane>(enemyBulletColor, whichShape, 100);
        newEnemy->setVisibility(false);
        newEnemy->setActorTickable(false);
        enemyAirplanes.push_back(newEnemy);
    }

    boss1 = spawnActor<EnemyAirplane>(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::BOSS1, 100);
    boss1->setVisibility(false);
    boss1->setActorTickable(false);
    boss1->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_STAR);

    boss2 = spawnActor<EnemyAirplane>(BULLET_COLOR::RED, ENEMY_SHIP_SHAPE::BOSS2, 100);
    boss2->setVisibility(false);
    boss2->setActorTickable(false);
    boss2->setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_STAR);

    shopCanvas = new ShopCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    shopCanvas->addToViewport();

    inGameCanvas = new InGameCanvas(Framework::rendererWidth, Framework::rendererHeight, 0, 0);
    inGameCanvas->removeFromViewport();

    bulletPool = new ActorObjectPool<Bullet>(500);
}

void MainLevel::exit()
{

}

void MainLevel::killAllEnemyAirplane()
{
    for(auto&enemy:enemyAirplanes)
    {
        if(enemy->getVisibility())
        {
            enemy->getDamage(99999);
        }
    }
}

void MainLevel::stageClear()
{
    isClear = true;
}

void MainLevel::afterStageClear()
{
    playerController->changeInputMode(INPUT_MODE::UI_ONLY);
    ShopCanvas* curCanvas = Cast<ShopCanvas>(shopCanvas);
    if(curCanvas->getMaxStage() == curCanvas->getCurStage() && !playerAirplane->getIsDie())
    {
        curCanvas->incMaxStage();
    }
    shopCanvas->addToViewport();
    playerAirplane->setVisibility(false);
    playerAirplane->setActorTickable(false);
    playerAirplane->getRootComponent()->setComponentLocalLocation(std::make_pair(Framework::rendererWidth / 2,
                                                                                 Framework::rendererHeight - 300));
    for(auto& enemy:enemyAirplanes)
    {
        if(enemy->getVisibility())
        {
            enemy->resetEnemyAirplaneToInitialState();
        }
    }
    if(boss1->getVisibility())
    {
        boss1->resetEnemyAirplaneToInitialState();
    }
    if(boss2->getVisibility())
    {
        boss2->resetEnemyAirplaneToInitialState();
    }
    inGameCanvas->removeFromViewport();

    isClear = false;

    coolTime = maxCoolTime;
}
