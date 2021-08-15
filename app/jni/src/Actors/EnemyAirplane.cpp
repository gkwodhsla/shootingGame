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

    rootComponent->setOwner(this);
    rootComponent->setComponentLocalLocation(std::make_pair(-999, -999));
    rootComponent->setComponentLocalRotation(0);

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
}

void EnemyAirplane::update(float deltaTime)
{
    HPawn::update(deltaTime);
    if(curHp<=0 && explosionSprite->getIsPlayEnd())
    {
        resetEnemyAirplaneToInitialState();
    }
    if(tickable && t < float(path->getControlPointSize() - 1) - 0.1f)
    {
        t += 0.001f;
        auto loc = path->getCurrentLocation(t);
        rootComponent->setComponentLocalLocation(std::make_pair(float(loc.first), float(loc.second)));
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
    tickable = false;
    visibility = false;
    t = 0.0f;
    this->path = nullptr;
    curHp = maxHP;
    airplaneImg->setVisibility(true);
    rootComponent->setComponentLocalLocation(std::make_pair(-999.0f,-999.0f));
    float barSize = float(hpBarRowSize) / float(maxHP);
    hpBar->setScale(std::make_pair(barSize * float(curHp), hpBarColSize));
}


void EnemyAirplane::setPath(SplineComponent* path)
{
    this->path = path;
}
