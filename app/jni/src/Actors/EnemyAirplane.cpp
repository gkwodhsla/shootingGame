#include "EnemyAirplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/SplineComponent.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "StageManager.h"
#include <android/log.h>
#include <random>

std::uniform_int_distribution<int> randomRotation(0, 360);

Vector2D EnemyAirplane::bullet3DirVec[3];
Vector2D EnemyAirplane::bullet5DirVec[5];
Vector2D EnemyAirplane::bullet7DirVec[7];
Vector2D EnemyAirplane::bossCirclePattern[30];
Vector2D EnemyAirplane::bossStarPattern[51];
Vector2D EnemyAirplane::bossStarPatternStartPos[51];
Vector2D EnemyAirplane::bossFlowerPattern[40];
Vector2D EnemyAirplane::bossFlowerPatternStartPos[40];

bool EnemyAirplane::isInitStaticData = false;

EnemyAirplane::EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape, int hp):bulletColor(color), shipShape(shape), curHp(hp), maxHP(hp)
{
    if(!isInitStaticData)
    {
        initStaticData();
    }
    if(shape == ENEMY_SHIP_SHAPE::SHIP1)
    {
        airplaneImg->changeImage("image/enemy/ship1.png");
    }
    else if(shape == ENEMY_SHIP_SHAPE::SHIP2)
    {
        airplaneImg->changeImage("image/enemy/ship2.png");
    }
    else if(shape == ENEMY_SHIP_SHAPE::SHIP3)
    {
        airplaneImg->changeImage("image/enemy/ship3.png");
    }
    else if(shape == ENEMY_SHIP_SHAPE::SHIP4)
    {
        airplaneImg->changeImage("image/enemy/ship4.png");
    }
    else if(shape == ENEMY_SHIP_SHAPE::BOSS1)
    {
        airplaneImg->changeImage("image/enemy/boss1.png");
    }
    else if(shape == ENEMY_SHIP_SHAPE::BOSS2)
    {
        airplaneImg->changeImage("image/enemy/boss2.png");
    }

    dirVec.x = 0.0f;
    dirVec.y = 1.0f;
    rootComponent->setOwner(this);
    rootComponent->setComponentLocalLocation(std::make_pair(-999, -999));
    rootComponent->setComponentLocalRotation(0);
    befPos = std::make_pair(-999, -999);

    hpBar = new ImageComponent("image/misc/hpBar.png",std::make_pair(0, 0), this);
    hpBar->setAffectRotationFromParent(false);
    hpBar->attachTo(airplaneImg);
    airplaneImg->setScale(std::make_pair(160, 160));
    if(shape == ENEMY_SHIP_SHAPE::BOSS1 || shape == ENEMY_SHIP_SHAPE::BOSS2)
    {
        airplaneImg->setScale(std::make_pair(500, 450));
    }
    auto shipImgSize = airplaneImg->getScale();

    hpBar->setComponentLocalLocation(std::make_pair((shipImgSize.first - hpBarRowSize) / 2, shipImgSize.second + 15));
    hpBar->setScale(std::make_pair(hpBarRowSize, hpBarColSize));

    turnOffBooster();

    collisionBox->setWidthAndHeight(shipImgSize.first, shipImgSize.second);
    collisionBox->setOwner(this);
    //적 기체에선 우선 부스터를 쓰지 않을 거라 꺼준다.

    explosionSprite->setOwner(this);
    explosionSprite->setComponentLocalLocation(std::make_pair(-55.0f, -45.0f));
    if(shape == ENEMY_SHIP_SHAPE::BOSS1 || shape == ENEMY_SHIP_SHAPE::BOSS2)
    {
        explosionSprite->setComponentLocalLocation(std::make_pair(-100.0f, -100.0f));
        explosionSprite->setScale(std::make_pair(800,800));
    }


    realDirVec.x = 0.0f;
    realDirVec.y = 1.0f;
}

EnemyAirplane::~EnemyAirplane()
{
    delete hpBar;
    hpBar = nullptr;
}

void EnemyAirplane::render()
{
    HPawn::render();
    auto loc = rootComponent->getComponentLocalLocation();
    SDL_RenderDrawLine(Framework::renderer,
                       loc.first + 100, loc.second + 100, loc.first + 100 + dirVec.x * 300.0f, 100+loc.second + dirVec.y * 300.0f);
    SDL_SetRenderDrawColor(Framework::renderer, 0xFF, 0, 0, 0xFF);
    SDL_RenderDrawLine(Framework::renderer,
                       loc.first + 100, loc.second + 100, loc.first + 100 + realDirVec.x * 300.0f, 100+loc.second + realDirVec.y * 300.0f);

    for(int i = 0; i < 50; ++i)
    {
        SDL_RenderDrawPoint(Framework::renderer, bossStarPatternStartPos[i].x + 500, bossStarPatternStartPos[i].y + 500);
    }
}

void EnemyAirplane::update(float deltaTime)
{
    HPawn::update(deltaTime);
    if(curHp<=0 && explosionSprite->getIsPlayEnd())
    {
        resetEnemyAirplaneToInitialState();
    }
    if(tickable && airplaneImg->getVisibility() && t < float(path->getControlPointSize() - 1) - 0.1f)
    {
        t += deltaTime * moveRate;
        auto loc = path->getCurrentLocation(t);
        rootComponent->setComponentLocalLocation(std::make_pair(float(loc.first), float(loc.second)));
        //loc가 지금 위치, befPos가 이전 위치

        ++cnt;
        if(cnt%200==0) // 자주 업데이트 하면 비행기가 흔들흔들거림
        {
            float newDirVecX = float(loc.first - befPos.first);
            float newDirVecY = float(loc.second - befPos.second);
            auto befDirVec = realDirVec;
            dirVec.x = newDirVecX;
            dirVec.y = newDirVecY;
            dirVec.normalize();

            float befDotCur = befDirVec.innerProduct(dirVec);
            float befCrossCur = befDirVec.outerProduct(dirVec);

            float curRot = rootComponent->getComponentLocalRotation();
            float degree = acos(befDotCur) * 180.0f / 3.14f;
            degree = fmin(degree, 360.0f - degree);
            float rotDir = befCrossCur;// asin(befCrossCur);
            if (!isnan(curRot) && !isnan(degree))
            {
                if (rotDir >= 0)
                    degreeGap = +degree;//-degree;
                else if (rotDir < 0.0f)
                    degreeGap = -degree;
            }


            befPos = rootComponent->getComponentLocalLocation();
        }
    }

    if(path && t > float(path->getControlPointSize() - 1) - 0.1f)
    {
        dirVec.x = 0.0f;
        dirVec.y = 1.0f;
        auto befDirVec = realDirVec;
        float befDotCur = befDirVec.innerProduct(dirVec);
        float befCrossCur = befDirVec.outerProduct(dirVec);

        float curRot = rootComponent->getComponentLocalRotation();
        float degree = acos(befDotCur) * 180.0f / 3.14f;
        degree = fmin(degree, 360.0f - degree);
        float rotDir = asin(befCrossCur);
        if (!isnan(curRot) && !isnan(degree))
        {
            if (rotDir >= 0)
                degreeGap = +degree;//-degree;
            else if (rotDir < 0.0f)
                degreeGap = -degree;
        }
        isArrived = true;
    }


    if(!(-0.5f<degreeGap&&degreeGap<0.5f))
    {
        float curRootRot = rootComponent->getComponentLocalRotation();
        float interpValue = deltaTime * rotateRate;
        if(degreeGap>0)
        {
            degreeGap-=interpValue;
            realDirVec.rotateVector(interpValue);
            rootComponent->setComponentLocalRotation(curRootRot + interpValue);
        }
        else
        {
            degreeGap+=interpValue;
            realDirVec.rotateVector(-interpValue);
            rootComponent->setComponentLocalRotation(curRootRot - interpValue);
        }
    }


    if(isArrived)
    {
        spawnBullet(deltaTime);
    }
}

void EnemyAirplane::handleEvent(SDL_Event &e)
{
    //적 비행기는 어떠한 이벤트도 받지 않는다.
    //하지만 확장성을 위해서 남겨는 둔다.
}

void EnemyAirplane::getDamage(int damage)
{
    curHp -= damage;
    if(curHp <= 0)
    {
        curHp = 0;
        explosionSprite->play();
        airplaneImg->setVisibility(false);
        canDamaged = false;

        MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
        if(shipShape == ENEMY_SHIP_SHAPE::BOSS1 || shipShape == ENEMY_SHIP_SHAPE::BOSS2)
        {
            mainLevel->stageManager->bossDie();
        }
        else
        {
            mainLevel->stageManager->enemyAirplaneDie();
        }
    }
    float barSize = float(hpBarRowSize) / float(maxHP);
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
}

void EnemyAirplane::resetEnemyAirplaneToInitialState()
{
    t = 0.0f;
    this->path->setUsable(true);
    this->path = nullptr;
    curHp = maxHP;
    float barSize = float(hpBarRowSize) / float(maxHP);
    airplaneImg->setVisibility(true);
    rootComponent->setComponentLocalLocation(std::make_pair(-999.0f,-999.0f));
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
    tickable = false;
    visibility = false;
    //dirVec = std::make_pair(0.0f, 1.0f);
    dirVec.x = 0.0f;
    dirVec.y = 1.0f;
    rootComponent->setComponentLocalRotation(0.0f);
    befPos = std::make_pair(-999, -999);
    canDamaged = false;
    curFireTime = fireRate;
    isArrived = false;
}


void EnemyAirplane::setPath(SplineComponent* path)
{
    this->path = path;
}

void EnemyAirplane::setCanDamaged(bool canDamaged)
{
    this->canDamaged = canDamaged;
}

bool EnemyAirplane::getCanDamaged()
{
    return canDamaged;
}

void EnemyAirplane::setBulletPattern(ENEMY_BULLET_PATTERN pattern)
{
    bulletPattern = pattern;
}

void EnemyAirplane::setMaxHP(int maxHP)
{
    this->maxHP = maxHP;
    this->curHp = maxHP;
}

void EnemyAirplane::firePattern1()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 2;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet3DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::BLUE:
            cont = mainLevel->enemyBlueBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet3DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::SKY:
            cont = mainLevel->enemySkyBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet3DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::PURPLE:
            cont = mainLevel->enemyPurpleBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet3DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::firePattern2()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 4;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet5DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::BLUE:
            cont = mainLevel->enemyBlueBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet5DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::SKY:
            cont = mainLevel->enemySkyBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet5DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::PURPLE:
            cont = mainLevel->enemyPurpleBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet5DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::firePattern3()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 6;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet7DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::BLUE:
            cont = mainLevel->enemyBlueBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet7DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::SKY:
            cont = mainLevel->enemySkyBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet7DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::PURPLE:
            cont = mainLevel->enemyPurpleBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bullet7DirVec[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::firePattern4()
{
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;

    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();
    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    auto playerLoc = mainLevel->playerAirplane->getRootComponent()->getComponentLocalLocation();

    auto newVectorX = playerLoc.first - worldLoc.first;
    auto newVectorY = playerLoc.second - worldLoc.second;

    Vector2D bulletDir = Vector2D(newVectorX, newVectorY);
    bulletDir.normalize();

    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bulletDir);
                    break;
                }
            }
            break;
        case BULLET_COLOR::BLUE:
            cont = mainLevel->enemyBlueBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bulletDir);
                    break;
                }
            }
            break;
        case BULLET_COLOR::SKY:
            cont = mainLevel->enemySkyBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bulletDir);
                    break;
                }
            }
            break;
        case BULLET_COLOR::PURPLE:
            cont = mainLevel->enemyPurpleBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    cont[i]->setActorDirectionalVector(bulletDir);
                    break;
                }
            }
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

float tempRotate = 0.0f;
void EnemyAirplane::firePattern5()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 29;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo(spawnPos); //총알액터의 위치를 세팅해준다.
                    bossCirclePattern[bulletCnt].rotateVector(tempRotate);
                    cont[i]->setActorDirectionalVector(bossCirclePattern[bulletCnt]);
                    --bulletCnt;
                    if(bulletCnt<0) break;
                }
            }
            tempRotate = randomRotation(dre);
            break;
        case BULLET_COLOR::BLUE:
            break;
        case BULLET_COLOR::SKY:
            break;
        case BULLET_COLOR::PURPLE:
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::firePattern6()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 0;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo({bossStarPatternStartPos[bulletCnt].x + spawnPos.first,
                                     bossStarPatternStartPos[bulletCnt].y + spawnPos.second}); //총알액터의 위치를 세팅해준다.
                    bossStarPattern[bulletCnt].rotateVector(tempRotate);
                    cont[i]->setActorDirectionalVector(bossStarPattern[bulletCnt]);
                    ++bulletCnt;
                    if(bulletCnt>49) break;
                }
            }
            tempRotate = randomRotation(dre);
            break;
        case BULLET_COLOR::BLUE:
            break;
        case BULLET_COLOR::SKY:
            break;
        case BULLET_COLOR::PURPLE:
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::firePattern7()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{worldLoc.first + size.first / 2, worldLoc.second + size.second};

    int bulletCnt = 0;
    MainLevel* mainLevel = (MainLevel*)Framework::curLevel;
    std::vector<Bullet*> cont;
    switch (bulletColor)
    {
        case BULLET_COLOR::RED:
            cont = mainLevel->enemyRedBullets;
            for(int i = 0; i < cont.size(); ++i)
            {
                if(!cont[i]->getVisibility()) //만약 총알의 visbility가 꺼져있다면 해당 버퍼는 사용가능!
                {
                    cont[i]->setVisibility(true);
                    cont[i]->setActorTickable(true);
                    cont[i]->moveTo({bossFlowerPatternStartPos[bulletCnt].x + spawnPos.first,
                                     bossFlowerPatternStartPos[bulletCnt].y + spawnPos.second}); //총알액터의 위치를 세팅해준다.
                    bossFlowerPattern[bulletCnt].rotateVector(tempRotate);
                    cont[i]->setActorDirectionalVector(bossFlowerPattern[bulletCnt]);
                    ++bulletCnt;
                    if(bulletCnt>39) break;
                }
            }
            tempRotate = randomRotation(dre);
            break;
        case BULLET_COLOR::BLUE:
            break;
        case BULLET_COLOR::SKY:
            break;
        case BULLET_COLOR::PURPLE:
            break;
        case BULLET_COLOR::GREEN: //플레이어 총알이기에 아무것도 안한다!!!
            break;
    }
}

void EnemyAirplane::spawnBullet(float deltaTime)
{
    curFireTime -= deltaTime;
    if(curFireTime <= 0.0f)
    {
        curFireTime = fireRate;
        switch (bulletPattern)
        {
            case ENEMY_BULLET_PATTERN::BULLET_3:
                firePattern1();
                break;
            case ENEMY_BULLET_PATTERN::BULLET_5:
                firePattern2();
                break;
            case ENEMY_BULLET_PATTERN::BULLET_7:
                firePattern3();
                break;
            case ENEMY_BULLET_PATTERN::TARGETED:
                firePattern4();
                break;
            case ENEMY_BULLET_PATTERN::BOSS_CIRCLE:
                firePattern5();
                break;
            case ENEMY_BULLET_PATTERN::BOSS_STAR:
                firePattern6();
                break;
            case ENEMY_BULLET_PATTERN::BOSS_FLOWER:
                firePattern7();
                break;
        }
    }
}

void EnemyAirplane::initStaticData()
{
    EnemyAirplane::isInitStaticData = true;

    Vector2D temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-15.0f);

    for(int i = 0; i < 3; ++i)
    {
        bullet3DirVec[i] = temp;
        temp.rotateVector(15.0f);
    }

    temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-30.0f);
    for(int i = 0; i < 5; ++i)
    {
        bullet5DirVec[i] = temp;
        temp.rotateVector(15.0f);
    }

    temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-45.0f);
    for(int i = 0; i < 7; ++i)
    {
        bullet7DirVec[i] = temp;
        temp.rotateVector(15.0f);
    }
    initBossCirclePattern();
    initBossStarPattern();
    initBossHeartPattern();
}

void EnemyAirplane::initBossCirclePattern() //이곳에서 보스 총알의 방향벡터를 계산해둔다. (circle)
{
    float toRad = 3.14f / 180.0f;
    float t = 0.0f; //클래스에서 쓰이는 t와 다르다. 로컬t임

    Vector2D befDir{1.0f, 0.0f};
    Vector2D curDir{0.0f, 0.0f};
    int index = 0;
    for(t = 0.0333f; t <= 1.0f; t += 0.0333f)
    {
        float curX = cos(t * 360.0f * toRad);
        float curY = sin(t * 360.0f * toRad);
        curDir = Vector2D{curX, curY};

        Vector2D v1 = curDir - befDir;
        v1.normalize();
        bossCirclePattern[index++] = Vector2D(v1.y, -v1.x);
        //Up vector를 (0, 0, -1.0f)라고 가정하고 v1과 외적한 결과이다.

        befDir = curDir;

    }
}

void EnemyAirplane::initBossStarPattern()
{
    //{xy=−9sin(2t)−5sin(3t)=9cos(2t)−5cos(3t)t∈[0,2π]
    float t = 0.0f;
    int index = 0;
    Vector2D befDir{-9 * sin(2 * t) - 5 * sin(3 * t), 9 * cos(2 * t) - 5 * cos(3 * t)};
    bossStarPatternStartPos[index] = befDir;
    //befDir.normalize();
    Vector2D curDir{0.0f, 0.0f};

    for(t = 0.1256f; t <= 3.14f * 2.0f; t += 0.1256f)
    {
        float curX = -9 * sin(2 * t) - 5 * sin(3 * t);
        float curY = 9 * cos(2 * t) - 5 * cos(3 * t);
        curDir = Vector2D{curX, curY};

        Vector2D v1 = curDir - befDir;
        //v1.normalize();
        if(abs(v1.x)>=3.5f)
            v1.x = 1.5f;
        bossStarPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossStarPatternStartPos[index] = Vector2D{curX * 10.0f, curY * 10.0f};
    }

    for(int i = 0; i < 50; ++i)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "%d번째 x: %f, y:%f", i, bossStarPattern[i].x, bossStarPattern[i].y);
    }
}

void EnemyAirplane::initBossHeartPattern()
{
    float t = 0.0f;
    int index = 0;
    Vector2D befDir{20*cos(3*t)*cos(t), 20*cos(3*t)*sin(t)};
    bossFlowerPatternStartPos[index] = befDir;
    //befDir.normalize();
    Vector2D curDir{0.0f, 0.0f};

    for(t = 0.08f; t <= 3.2f; t += 0.08f)
    {
        float curX = 20*cos(3*t)*cos(t);
        float curY = 20*cos(3*t)*sin(t);
        curDir = Vector2D{curX, curY};

        Vector2D v1 = curDir - befDir;
        v1.normalize();
        //if(abs(v1.x)>=3.5f)
            //v1.x = 1.5f;
        bossFlowerPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossFlowerPatternStartPos[index] = Vector2D{curX * 10.0f, curY * 10.0f};
    }
}