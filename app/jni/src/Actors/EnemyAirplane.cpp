#include "EnemyAirplane.h"
#include "StageManager.h"
#include "Crystal.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/SplineComponent.h"
#include "../Components/AudioComponent.h"
#include "Airplane.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../GlobalFunction.h"
#include "../ActorObjectPool.h"
#include "../Actors/Bullet.h"
#include <android/log.h>
#include <random>

using namespace GlobalFunction;

std::uniform_int_distribution<int> randomRotation(0, 360);

const float EnemyAirplane::normalBulletSpeed = 700.0f;
Vector2D EnemyAirplane::bullet3DirVec[3];
Vector2D EnemyAirplane::bullet5DirVec[5];
Vector2D EnemyAirplane::bullet7DirVec[7];
Vector2D EnemyAirplane::bossCirclePattern[31];
Vector2D EnemyAirplane::bossStarPattern[51];
Vector2D EnemyAirplane::bossStarPatternStartPos[51];
Vector2D EnemyAirplane::bossFlowerPattern[41];
Vector2D EnemyAirplane::bossFlowerPatternStartPos[41];

bool EnemyAirplane::isInitStaticData = false;


EnemyAirplane::EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape, int hp) :bulletColor(color), shipShape(shape), curHp(hp), maxHP(hp)
{
    if (!isInitStaticData)
    {
        initStaticData();
    }

    switch (shape)
    {
        case ENEMY_SHIP_SHAPE::SHIP1:
            airplaneImg = new ImageComponent("image/enemy/ship1.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP2:
            airplaneImg = new ImageComponent("image/enemy/ship2.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP3:
            airplaneImg = new ImageComponent("image/enemy/ship3.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP4:
            airplaneImg = new ImageComponent("image/enemy/ship4.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::BOSS1:
            airplaneImg = new ImageComponent("image/enemy/boss1.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::BOSS2:
            airplaneImg = new ImageComponent("image/enemy/boss2.png", std::make_pair(0, 0), this);
            break;
    }
    airplaneImg->attachTo(rootComponent);
    airplaneImg->setScale(std::make_pair(160, 160));
    if (shape == ENEMY_SHIP_SHAPE::BOSS1 || shape == ENEMY_SHIP_SHAPE::BOSS2)
    {
        airplaneImg->setScale(std::make_pair(500, 450));
    }

    dirVec.x = 0.0f;
    dirVec.y = 1.0f;

    rootComponent->setComponentLocalLocation(std::make_pair(-999, -999));
    rootComponent->setComponentLocalRotation(0);
    befPos = std::make_pair(-999, -999);

    hpBar = new ImageComponent("image/misc/hpBar.png", std::make_pair(0, 0), this);
    hpBar->attachTo(airplaneImg);
    hpBar->setAffectRotationFromParent(false);

    auto shipImgSize = airplaneImg->getScale();
    hpBar->setComponentLocalLocation(std::make_pair((shipImgSize.first - hpBarRowSize) / 2, shipImgSize.second + 15));
    hpBar->setScale(std::make_pair(hpBarRowSize, hpBarColSize));

    collisionBox->setWidthAndHeight(shipImgSize.first, shipImgSize.second);
    auto collisionResponse = [this](HActor* other) mutable
    {
        Bullet* bullet = Cast<Bullet>(other);
        if(bullet && bullet->getIsPlayerBullet()) //부딪힌 오브젝트가 총알이면
        {
            if(getCanDamaged())//데미지를 입을 수 있는 상태라면
            {
                Airplane* playerAirplane = Cast<Airplane>(GetPlayerPawn());
                if(playerAirplane)
                {
                    this->getDamage(playerAirplane->getPlayerAttackPower());
                    bullet->resetBulletToInitialState();
                    isHitAnimPlay = true;
                }
            }
        }
    };
    collisionBox->registerCollisionResponse(collisionResponse);

    explosionSprite->setComponentLocalLocation(std::make_pair(-55.0f, -45.0f));
    if (shape == ENEMY_SHIP_SHAPE::BOSS1 || shape == ENEMY_SHIP_SHAPE::BOSS2)
    {
        explosionSprite->setComponentLocalLocation(std::make_pair(-100.0f, -100.0f));
        explosionSprite->setScale(std::make_pair(800, 800));
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
    AirplaneParent::render();
    auto loc = rootComponent->getComponentLocalLocation();
    SDL_RenderDrawLine(Framework::renderer,
                       loc.first + 100, loc.second + 100, loc.first + 100 + dirVec.x * 300.0f, 100 + loc.second + dirVec.y * 300.0f);
    SDL_SetRenderDrawColor(Framework::renderer, 0xFF, 0, 0, 0xFF);
    SDL_RenderDrawLine(Framework::renderer,
                       loc.first + 100, loc.second + 100, loc.first + 100 + realDirVec.x * 300.0f, 100 + loc.second + realDirVec.y * 300.0f);
}

void EnemyAirplane::update(float deltaTime)
{
    AirplaneParent::update(deltaTime);
    if (isDie && explosionSprite->getIsPlayEnd())
    {
        resetEnemyAirplaneToInitialState();
    }
    if (path && tickable && airplaneImg->getVisibility() && t < float(path->getControlPointSize() - 1) - 0.1f)
    {
        t += deltaTime * moveRate;
        auto loc = path->getCurrentLocation(t);
        rootComponent->setComponentLocalLocation(std::make_pair(float(loc.first), float(loc.second)));
        //loc가 지금 위치, befPos가 이전 위치

        ++cnt;
        if (cnt % 10 == 0) // 자주 업데이트 하면 비행기가 흔들흔들거림
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

    if (path && t > float(path->getControlPointSize() - 1) - 0.1f)
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


    if (!(-0.5f < degreeGap && degreeGap < 0.5f))
    {
        float curRootRot = rootComponent->getComponentLocalRotation();
        float interpValue = deltaTime * rotateRate;
        if (degreeGap > 0)
        {
            degreeGap -= interpValue;
            realDirVec.rotateVector(interpValue);
            rootComponent->setComponentLocalRotation(curRootRot + interpValue);
        }
        else
        {
            degreeGap += interpValue;
            realDirVec.rotateVector(-interpValue);
            rootComponent->setComponentLocalRotation(curRootRot - interpValue);
        }
    }
    if (isArrived)
    {
        spawnBullet(deltaTime);
    }

    hitAnimation(deltaTime);
}

void EnemyAirplane::handleEvent(SDL_Event& e)
{
    //적 비행기는 어떠한 이벤트도 받지 않는다.
}

void EnemyAirplane::getDamage(int damage)
{
    curHp -= damage;
    if (curHp <= 0)
    {
        explosionAudio->play();
        curHp = 0;
        explosionSprite->play();
        airplaneImg->setVisibility(false);
        canDamaged = false;

        MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);

        if (shipShape == ENEMY_SHIP_SHAPE::BOSS1 || shipShape == ENEMY_SHIP_SHAPE::BOSS2)
        {
            mainLevel->stageManager->bossDie();
        }
        else
        {
            mainLevel->stageManager->enemyAirplaneDie();
        }
        isDie = true;

        auto spawnedCrystal = mainLevel->crystalPool->acquireObject();
        spawnedCrystal->getRootComponent()->setComponentLocalLocation(getActorWorldLocation());
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
    rootComponent->setComponentLocalLocation(std::make_pair(-999.0f, -999.0f));
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
    tickable = false;
    visibility = false;
    //dirVec = std::make_pair(0.0f, 1.0f);
    dirVec.x = 0.0f;
    dirVec.y = 1.0f;
    realDirVec.x = 0.0f;
    realDirVec.y = 1.0f;
    rootComponent->setComponentLocalRotation(0.0f);
    befPos = std::make_pair(-999, -999);
    canDamaged = false;
    curFireTime = fireRate;
    isArrived = false;
    isDie = false;
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

void EnemyAirplane::setIsDie(bool isDie)
{
    AirplaneParent::setIsDie(isDie);
}

bool EnemyAirplane::getIsDie()
{
    return AirplaneParent::getIsDie();
}

void EnemyAirplane::setFireRate(float rate)
{
    AirplaneParent::setFireRate(rate);
}

void EnemyAirplane::firePattern1()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 3;

    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool(spawnPos, normalBulletSpeed, bullet3DirVec[i]);
    }

}

void EnemyAirplane::firePattern2()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 5;
    for(int i = 0; i < bulletCnt;++i)
    {
        spawnBulletFromPool(spawnPos, normalBulletSpeed, bullet5DirVec[i]);
    }
}

void EnemyAirplane::firePattern3()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 7;
    for(int i = 0; i < bulletCnt;++i)
    {
        spawnBulletFromPool(spawnPos, normalBulletSpeed, bullet7DirVec[i]);
    }
}

void EnemyAirplane::firePattern4()
{
    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
    std::vector<Bullet*> cont;

    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();
    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    auto playerLoc = mainLevel->playerAirplane->getRootComponent()->getComponentLocalLocation();

    auto newVectorX = playerLoc.first - worldLoc.first;
    auto newVectorY = playerLoc.second - worldLoc.second;

    Vector2D bulletDir = Vector2D(newVectorX, newVectorY);
    bulletDir.normalize();

    spawnBulletFromPool(spawnPos, normalBulletSpeed, bulletDir);

}

float tempRotate = 0.0f;
void EnemyAirplane::firePattern5()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 30;

    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool(spawnPos, 1200.0f, bossCirclePattern[i]);
        bossCirclePattern[i].rotateVector(tempRotate);
    }
    tempRotate = randomRotation(dre);
}

void EnemyAirplane::firePattern6()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 49;
    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool({bossStarPatternStartPos[i].x + spawnPos.first,bossStarPatternStartPos[i].y + spawnPos.second },
                            500.0f, bossStarPattern[i]);
        bossStarPattern[i].rotateVector(tempRotate);
    }
    tempRotate = randomRotation(dre);
}

void EnemyAirplane::firePattern7()
{
    auto worldLoc = rootComponent->getComponentLocalLocation();
    auto size = airplaneImg->getScale();

    std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

    int bulletCnt = 40;
    for(int i = 0; i < bulletCnt; ++i)
    {
        spawnBulletFromPool({bossFlowerPatternStartPos[i].x + spawnPos.first,
                             bossFlowerPatternStartPos[i].y + spawnPos.second}, 900.0f,
                            bossFlowerPattern[i]);
        bossFlowerPattern[i].rotateVector(tempRotate);
    }
    tempRotate = randomRotation(dre);
}

void EnemyAirplane::spawnBullet(float deltaTime)
{
    curFireTime -= deltaTime;
    if (curFireTime <= 0.0f)
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

    for (int i = 0; i < 3; ++i)
    {
        bullet3DirVec[i] = temp;
        temp.rotateVector(15.0f);
    }

    temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-30.0f);
    for (int i = 0; i < 5; ++i)
    {
        bullet5DirVec[i] = temp;
        temp.rotateVector(15.0f);
    }

    temp = Vector2D(0.0f, 1.0f);
    temp.rotateVector(-45.0f);
    for (int i = 0; i < 7; ++i)
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

    Vector2D befDir{ 1.0f, 0.0f };
    Vector2D curDir{ 0.0f, 0.0f };
    int index = 0;
    for (t = 0.0333f; t <= 1.0f; t += 0.0333f)
    {
        float curX = cos(t * 360.0f * toRad);
        float curY = sin(t * 360.0f * toRad);
        curDir = Vector2D{ curX, curY };

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
    Vector2D befDir{ -9 * sin(2 * t) - 5 * sin(3 * t), 9 * cos(2 * t) - 5 * cos(3 * t) };
    bossStarPatternStartPos[index] = befDir;
    //befDir.normalize();
    Vector2D curDir{ 0.0f, 0.0f };

    for (t = 0.1256f; t <= 3.14f * 2.0f; t += 0.1256f)
    {
        float curX = -9 * sin(2 * t) - 5 * sin(3 * t);
        float curY = 9 * cos(2 * t) - 5 * cos(3 * t);
        curDir = Vector2D{ curX, curY };

        Vector2D v1 = curDir - befDir;
        //v1.normalize();
        if (abs(v1.x) >= 3.5f)
            v1.x = 1.5f;
        bossStarPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossStarPatternStartPos[index] = Vector2D{ curX * 10.0f, curY * 10.0f };
    }

    for (int i = 0; i < 50; ++i)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "%d번째 x: %f, y:%f", i, bossStarPattern[i].x, bossStarPattern[i].y);
    }
}

void EnemyAirplane::initBossHeartPattern()
{
    float t = 0.0f;
    int index = 0;
    Vector2D befDir{ 20 * cos(3 * t) * cos(t), 20 * cos(3 * t) * sin(t) };
    bossFlowerPatternStartPos[index] = befDir;
    //befDir.normalize();
    Vector2D curDir{ 0.0f, 0.0f };

    for (t = 0.08f; t <= 3.2f; t += 0.08f)
    {
        float curX = 20 * cos(3 * t) * cos(t);
        float curY = 20 * cos(3 * t) * sin(t);
        curDir = Vector2D{ curX, curY };

        Vector2D v1 = curDir - befDir;
        v1.normalize();
        //if(abs(v1.x)>=3.5f)
        //v1.x = 1.5f;
        bossFlowerPattern[index++] = Vector2D(v1.y, -v1.x);

        befDir = curDir;
        bossFlowerPatternStartPos[index] = Vector2D{ curX * 10.0f, curY * 10.0f };
    }
}

void EnemyAirplane::spawnBulletFromPool(const std::pair<float, float>&spawnPos, float speed, const Vector2D& dirVec)
{
    MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
    ActorObjectPool<Bullet>* cont;
    cont = mainLevel->bulletPool;
    auto bullet = cont->acquireObject();
    bullet->init(spawnPos, bulletColor);
    bullet->setActorDirectionalVector(dirVec);
    bullet->changeBulletSpeed(speed);

}

void EnemyAirplane::hitAnimation(float deltaTime)
{
    if(isHitAnimPlay)
    {
        animAccTime+=deltaTime;
        float animTime = fmod(animAccTime, 0.3f) - 0.15f;
        float yValue = (20.0f / 3.0f) * animTime + 1;
        airplaneImg->setImageColor(yValue * 255, yValue * 255, yValue * 255);
        if(animAccTime >= 0.3f)
        {
            isHitAnimPlay = false;
            airplaneImg->setImageColor(255, 255, 255);
            animAccTime = 0.0f;
        }
    }
}