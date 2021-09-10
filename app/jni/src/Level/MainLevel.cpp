#include "MainLevel.h"

#include "../Actors/HActor.h"
#include "../Actors/BackgroundActor.h"
#include "../Actors/Airplane.h"
#include "../Actors/EnemyAirplane.h"
#include "../Actors/Crystal.h"
#include "../Actors/Spawner.h"
#include "../Actors/StageManager.h"
#include "../HPlayerController.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SplineComponent.h"
#include "../UI/ShopCanvas.h"
#include "../UI/InGameCanvas.h"
#include "../UI/CashShopCanvas.h"
#include "../ActorObjectPool.h"
#include "../GlobalFunction.h"
#include "../AirplaneController.h"
#include "../DBManager.h"
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
    setID(GlobalFunction::GetClassTypeUniqueID<MainLevel>());
}

MainLevel::~MainLevel()
{
    delete bulletPool;
    bulletPool = nullptr;

    delete crystalPool;
    crystalPool = nullptr;
}

void MainLevel::handleEvent(const SDL_Event& e)
{
    HLevelBase::handleEvent(e);
}

void MainLevel::update(float deltaTime)
{
    HLevelBase::update(deltaTime);

    AirplaneController* PC = Cast<AirplaneController>(playerController);

    ShopCanvas* curCanvas = Cast<ShopCanvas>(PC->shopCanvas);

    if(curCanvas->getIsPlayButtonClicked())
    {
        bgActor->playBattleMusic();
        playerAirplane->playerInitWhenStageBegin();
        curCanvas->removeFromViewport();
        curCanvas->setIsPlayButtonClicked(false);
        playerController->changeInputMode(INPUT_MODE::BOTH);
        stageManager->setStage(curCanvas->getCurStage());
        stageManager->waveBegin();
        PC->inGameCanvas->addToViewport();
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
    bgActor = spawnActor<BackgroundActor>();
    stageManager = spawnActor<StageManager>();
    playerAirplane = spawnActor<Airplane>();
    playerAirplane->setVisibility(false);
    playerAirplane->setActorTickable(false);

    playerController = new AirplaneController(playerAirplane);
    playerController->possess(playerAirplane);
    playerController->changeInputMode(INPUT_MODE::UI_ONLY);
    auto PC = Cast<AirplaneController>(playerController);
    PC->createCanvases();

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
    bulletPool = new ActorObjectPool<Bullet>(500);
    crystalPool = new ActorObjectPool<Crystal>(50);

    initDataUsingDataReadFromDB();

    bgActor->stopBattleMusic();
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
    bgActor->stopBattleMusic();

    playerController->changeInputMode(INPUT_MODE::UI_ONLY);
    auto* PC = Cast<AirplaneController>(playerController);

    auto* curCanvas = Cast<ShopCanvas>(PC->shopCanvas);

    if(curCanvas->getMaxStage() == curCanvas->getCurStage() && !playerAirplane->getIsDie())
    {
        curCanvas->incMaxStage();
    }
    curCanvas->setMissileCnt(playerAirplane->getThunderCnt());
    curCanvas->setShieldCnt(playerAirplane->getShieldCnt());
    curCanvas->updateShopState();
    curCanvas->addToViewport();

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
    PC->inGameCanvas->removeFromViewport();

    isClear = false;

    coolTime = maxCoolTime;

    writeGameDataToDB();
}

void MainLevel::writeGameDataToDB()
{
    auto PC = Cast<AirplaneController>(GetPlayerController());
    auto shopCanvas = Cast<ShopCanvas>(PC->shopCanvas);

    DBData writeData;

    writeData.attackUpgrade = shopCanvas->getAttackUpgrade();
    writeData.bulletUpgrade = shopCanvas->getBulletUpgrade();
    writeData.curAirplaneUpgrade = shopCanvas->getAirplaneUpgrade();
    writeData.thunderNum = playerAirplane->getThunderCnt();
    writeData.shieldNum = playerAirplane->getShieldCnt();
    writeData.money = shopCanvas->getCrystal();
    writeData.maxStage = shopCanvas->getMaxStage();
    writeData.curAttack = playerAirplane->getPlayerAttackPower();
    writeData.curBullet = playerAirplane->getPlayerBulletCnt();
    Framework::dbManager->writeToDB(writeData);
}

void MainLevel::initDataUsingDataReadFromDB()
{
    auto PC = Cast<AirplaneController>(GetPlayerController());
    auto shopCanvas = Cast<ShopCanvas>(PC->shopCanvas);

    auto data = Framework::dbManager->getDataReadFromDB();

    shopCanvas->setAttackUpgrade(data.attackUpgrade);
    shopCanvas->setBulletUpgrade(data.bulletUpgrade);
    shopCanvas->setAirplaneUpgrade(data.curAirplaneUpgrade);
    shopCanvas->setMissileCnt(data.thunderNum);
    shopCanvas->setShieldCnt(data.shieldNum);
    shopCanvas->setCrystal(data.money);
    shopCanvas->setMaxStage(data.maxStage);
    playerAirplane->setPlayerAttackPower(data.curAttack);
    playerAirplane->setPlayerBulletCnt(data.curBullet);
    playerAirplane->setThunderCnt(data.thunderNum);
    playerAirplane->setShieldCnt(data.shieldNum);

    if(data.curAirplaneUpgrade == 1)
    {
        playerAirplane->setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE::SHAPE1);
    }
    else if(data.curAirplaneUpgrade == 2)
    {
        playerAirplane->setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE::SHAPE2);
    }
    else
    {
        playerAirplane->setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE::SHAPE3);
    }
    shopCanvas->updateShopState();
}