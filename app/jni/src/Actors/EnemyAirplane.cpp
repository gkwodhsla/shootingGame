#include "EnemyAirplane.h"
#include "StageManager.h"
#include "Crystal.h"
#include "AttackStrategy/CircleStrategy.h"
#include "AttackStrategy/Fire3Strategy.h"
#include "AttackStrategy/Fire5Strategy.h"
#include "AttackStrategy/Fire7Strategy.h"
#include "AttackStrategy/FlowerStrategy.h"
#include "AttackStrategy/StarStrategy.h"
#include "AttackStrategy/TargetingStrategy.h"
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

std::uniform_int_distribution<int> bossNext(0, 2);

const float EnemyAirplane::normalBulletSpeed = 700.0f;
const float EnemyAirplane::circleBulletSpeed = 1200.0f;
const float EnemyAirplane::starBulletSpeed = 500.0f;
const float EnemyAirplane::flowerBulletSpeed = 1000.0f;
bool EnemyAirplane::isInitStaticData = false;

AttackStrategy* EnemyAirplane::circlePattern = nullptr;
AttackStrategy* EnemyAirplane::fire3Pattern = nullptr;
AttackStrategy* EnemyAirplane::fire5Pattern = nullptr;
AttackStrategy* EnemyAirplane::fire7Pattern = nullptr;
AttackStrategy* EnemyAirplane::flowerPattern = nullptr;
AttackStrategy* EnemyAirplane::starPattern = nullptr;
AttackStrategy* EnemyAirplane::targetingPattern = nullptr;


EnemyAirplane::EnemyAirplane(const BULLET_COLOR color, const ENEMY_SHIP_SHAPE shape, int hp) :bulletColor(color), shipShape(shape), curHp(hp), maxHP(hp)
{
    if (!isInitStaticData)
    {
        initStaticData();
    }

    switch (shape)
    {
        case ENEMY_SHIP_SHAPE::SHIP1:
            airplaneImg = createComponent<ImageComponent>("image/enemy/ship1.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP2:
            airplaneImg = createComponent<ImageComponent>("image/enemy/ship2.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP3:
            airplaneImg = createComponent<ImageComponent>("image/enemy/ship3.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::SHIP4:
            airplaneImg = createComponent<ImageComponent>("image/enemy/ship4.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::BOSS1:
            airplaneImg = createComponent<ImageComponent>("image/enemy/boss1.png", std::make_pair(0, 0), this);
            break;
        case ENEMY_SHIP_SHAPE::BOSS2:
            airplaneImg = createComponent<ImageComponent>("image/enemy/boss2.png", std::make_pair(0, 0), this);
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

    hpBar = createComponent<ImageComponent>("image/misc/hpBar.png", std::make_pair(0, 0), this);
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
    if(circlePattern)
    {
        delete circlePattern;
        circlePattern = nullptr;
    }
    if(fire3Pattern)
    {
        delete fire3Pattern;
        fire3Pattern = nullptr;
    }
    if(fire5Pattern)
    {
        delete fire5Pattern;
        fire5Pattern = nullptr;
    }
    if(fire7Pattern)
    {
        delete fire7Pattern;
        fire7Pattern = nullptr;
    }
    if(flowerPattern)
    {
        delete flowerPattern;
        flowerPattern = nullptr;
    }
    if(starPattern)
    {
        delete starPattern;
        starPattern = nullptr;
    }
    if(targetingPattern)
    {
        delete targetingPattern;
        targetingPattern = nullptr;
    }
}

void EnemyAirplane::render()
{
    AirplaneParent::render();
    //auto loc = rootComponent->getComponentLocalLocation();
    //SDL_RenderDrawLine(Framework::renderer,
    //                   loc.first + 100, loc.second + 100, loc.first + 100 + dirVec.x * 300.0f, 100 + loc.second + dirVec.y * 300.0f);
    //SDL_SetRenderDrawColor(Framework::renderer, 0xFF, 0, 0, 0xFF);
    //SDL_RenderDrawLine(Framework::renderer,
    //                   loc.first + 100, loc.second + 100, loc.first + 100 + realDirVec.x * 300.0f, 100 + loc.second + realDirVec.y * 300.0f);
}

void EnemyAirplane::update(const float deltaTime)
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

void EnemyAirplane::handleEvent(const SDL_Event& e)
{
    //적 비행기는 어떠한 이벤트도 받지 않는다.
}

void EnemyAirplane::getDamage(int damage)
{
    curHp -= damage;
    if (curHp <= 0 && !isDie)
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
    if(this->path)
    {
        this->path->setUsable(true);
        this->path = nullptr;
    }
    curHp = maxHP;
    float barSize = float(hpBarRowSize) / float(maxHP);
    airplaneImg->setVisibility(true);
    rootComponent->setComponentLocalLocation(std::make_pair(-999.0f, -999.0f));
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
    tickable = false;
    visibility = false;
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

void EnemyAirplane::setBulletPattern(const ENEMY_BULLET_PATTERN pattern)
{
    switch (pattern)
    {
        case ENEMY_BULLET_PATTERN::BULLET_3:
            curAttackStrategy = EnemyAirplane::fire3Pattern;
            break;
        case ENEMY_BULLET_PATTERN::BULLET_5:
            curAttackStrategy = EnemyAirplane::fire5Pattern;
            break;
        case ENEMY_BULLET_PATTERN::BULLET_7:
            curAttackStrategy = EnemyAirplane::fire7Pattern;
            break;
        case ENEMY_BULLET_PATTERN::TARGETED:
            curAttackStrategy = EnemyAirplane::targetingPattern;
            break;
        case ENEMY_BULLET_PATTERN::BOSS_CIRCLE:
            curAttackStrategy = EnemyAirplane::circlePattern;
            break;
        case ENEMY_BULLET_PATTERN::BOSS_STAR:
            curAttackStrategy = EnemyAirplane::starPattern;
            break;
        case ENEMY_BULLET_PATTERN::BOSS_FLOWER:
            curAttackStrategy = EnemyAirplane::flowerPattern;
            break;

    }
    bulletPattern = pattern;
}

void EnemyAirplane::setMaxHP(int maxHP)
{
    this->maxHP = maxHP;
    this->curHp = maxHP;
}


void EnemyAirplane::spawnBullet(float deltaTime)
{
    curFireTime -= deltaTime;
    if (curFireTime <= 0.0f)
    {
        curFireTime = fireRate;
        auto worldLoc = rootComponent->getComponentLocalLocation();
        auto size = airplaneImg->getScale();

        std::pair<int, int> spawnPos{ worldLoc.first + size.first / 2, worldLoc.second + size.second };

        if(shipShape == ENEMY_SHIP_SHAPE::BOSS1 || shipShape == ENEMY_SHIP_SHAPE::BOSS2)
        {
            int nextBossAttack = bossNext(dre);
            if(nextBossAttack == 0)
            {
                setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_CIRCLE);
                curAttackStrategy->attackAction(spawnPos, circleBulletSpeed, bulletColor);
            }
            else if(nextBossAttack == 1)
            {
                setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_STAR);
                curAttackStrategy->attackAction(spawnPos, starBulletSpeed, bulletColor);
            }
            else
            {
                setBulletPattern(ENEMY_BULLET_PATTERN::BOSS_FLOWER);
                curAttackStrategy->attackAction(spawnPos, flowerBulletSpeed, bulletColor);
            }
        }
        else
        {
            curAttackStrategy->attackAction(spawnPos, normalBulletSpeed, bulletColor);
        }
    }
}

void EnemyAirplane::initStaticData()
{
    EnemyAirplane::isInitStaticData = true;

    circlePattern = new CircleStrategy();
    fire3Pattern = new Fire3Strategy();
    fire5Pattern = new Fire5Strategy();
    fire7Pattern = new Fire7Strategy();
    flowerPattern = new FlowerStrategy();
    starPattern = new StarStrategy();
    targetingPattern = new TargetingStrategy();
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