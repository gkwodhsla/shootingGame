#include "EnemyAirplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/SplineComponent.h"
#include "../Framework.h"
#include <android/log.h>
EnemyAirplane::EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape, int hp):bulletColor(color), curHp(hp), maxHP(hp)
{
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
    dirVec = std::make_pair(0.0f, 1.0f);
    rootComponent->setOwner(this);
    rootComponent->setComponentLocalLocation(std::make_pair(-999, -999));
    rootComponent->setComponentLocalRotation(0);
    befPos = std::make_pair(-999, -999);

    hpBar = new ImageComponent("image/misc/hpBar.png",std::make_pair(0, 0), this);
    hpBar->attachTo(airplaneImg);
    auto shipImgSize = airplaneImg->getImageSize();

    hpBar->setComponentLocalLocation(std::make_pair((shipImgSize.first - hpBarRowSize) / 2, shipImgSize.second + 15));
    hpBar->setScale(std::make_pair(hpBarRowSize, hpBarColSize));

    turnOffBooster();

    collisionBox->setWidthAndHeight(shipImgSize.first, shipImgSize.second);
    collisionBox->setOwner(this);
    //적 기체에선 우선 부스터를 쓰지 않을 거라 꺼준다.

    explosionSprite->setOwner(this);
    explosionSprite->setComponentLocalLocation(std::make_pair(-55.0f, -45.0f));

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
                       loc.first + 100, loc.second + 100, loc.first + 100 + dirVec.first * 300.0f, 100+loc.second + dirVec.second * 300.0f);
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
        befPos = rootComponent->getComponentLocalLocation();
        t += deltaTime * 0.4f;
        auto loc = path->getCurrentLocation(t);
        rootComponent->setComponentLocalLocation(std::make_pair(float(loc.first), float(loc.second)));
        //loc가 지금 위치, befPos가 이전 위치

        //여기서 이전 방향벡터와 새로운 방향향
        float newDirVecX = float(loc.first - befPos.first);
        float newDirVecY = float(loc.second - befPos.second);
        auto befDirVec = std::make_pair(0.0f, 1.0f);
        dirVec.first = newDirVecX;
        dirVec.second = newDirVecY;
        normalizeDirVec();


        float befDotCur = (befDirVec.first * dirVec.first) + (befDirVec.second * dirVec.second);
        float befCrossCur = (befDirVec.first*dirVec.second) - (dirVec.first*befDirVec.second);

        float curRot = rootComponent->getComponentLocalRotation();
        float degree = acos(befDotCur) * 180.0f / 3.14f;
        degree = fmin(degree, 360.0f - degree);
        float rotDir = asin(befCrossCur);
        if (!isnan(curRot) && !isnan(degree))
        {
            float destRot = 0.0f;
            if(rotDir>=0)
                destRot = +degree;//-degree;
            else if(rotDir<0.0f)
                destRot = -degree;
            rootComponent->setComponentLocalRotation(destRot);

        }

        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "x: %f ", rootComponent->getComponentLocalRotation());

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
    float barSize = float(hpBarRowSize) / float(maxHP);
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
    if(curHp <= 0)
    {
        explosionSprite->play();
        airplaneImg->setVisibility(false);
    }
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
    dirVec = std::make_pair(0.0f, 1.0f);
    rootComponent->setComponentLocalRotation(0.0f);
    befPos = std::make_pair(-999, -999);
}


void EnemyAirplane::setPath(SplineComponent* path)
{
    this->path = path;
}
