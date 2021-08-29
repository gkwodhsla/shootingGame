#include <SDL.h>
#include <android/log.h>
#include <vector>
#include <cmath>
#include "Airplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../ActorObjectPool.h"
#include "../Framework.h"
#include "../Level/MainLevel.h"
#include "../Actors/Bullet.h"
#include "../GlobalFunction.h"

using namespace GlobalFunction;

Airplane::Airplane()
{
    rootComponent->setComponentLocalLocation(std::make_pair(Framework::rendererWidth / 2,
                                                            Framework::rendererHeight - 300));
    rootComponent->setComponentLocalRotation(0);
    rootComponent->setOwner(this);
    airplaneImg = new ImageComponent("image/player/1.png", std::make_pair(0, 0), this);
    airplaneImg->attachTo(rootComponent);
    airplaneImg->setScale({100, 115});

    auto airPlaneImgSize = airplaneImg->getScale();
    boosterSprite = new SpritesheetComponent("image/spritesheet/rocketFlame2.png",
                                             std::make_pair(airPlaneImgSize.first/2 - 13, airPlaneImgSize.second - 30),
                                             this, 2, 1, 2);
    boosterSprite->setDrawCntPerSec(8);
    boosterSprite->attachTo(airplaneImg);
    boosterSprite->setScale(std::make_pair(30,108));
    boosterSprite->setLooping(true);
    boosterSprite->setImageFlip(SDL_FLIP_VERTICAL);
    boosterSprite->play();

    explosionSprite = new SpritesheetComponent("image/spritesheet/explosion.png",
                                               std::make_pair(-80.0f, -45.0f), this, 24, 6, 4);
    explosionSprite->attachTo(rootComponent);
    explosionSprite->setScale(std::make_pair(350, 350));
    explosionSprite->setLooping(false);
    explosionSprite->setDrawCntPerSec(40);

    auto collisionResponse = [this](HActor* other) mutable
    {
        Bullet* bullet = Cast<Bullet>(other);
        MainLevel* mainLevel = Cast<MainLevel>(GetLevel());
        if(bullet && !bullet->getIsPlayerBullet() && !mainLevel->isClear) //부딪힌 오브젝트가 총알이고 적군의 총알이면
        {
            if(canDestroyable && !isDie)//데미지를 입을 수 있는 상태라면
            {
                airplaneImg->setVisibility(false);
                boosterSprite->setVisibility(false);
                explosionSprite->play();
                canDestroyable = false;
                isDie = true;
                MainLevel* mainLevel = Cast<MainLevel>(GetLevel());
                mainLevel->stageClear();
            }
        }
    };
    collisionBox = new CollisionBoxComponent(0, 0, airPlaneImgSize.first, airPlaneImgSize.second, this);
    collisionBox->setDrawDebugBox(true);
    collisionBox->attachTo(rootComponent);
    collisionBox->registerCollisionResponse(collisionResponse);

    shieldImage = new ImageComponent("image/misc/shield.png",{-50, -50},this);
    //shieldImage->setAlpha(140);
    shieldImage->setScale({200, 200});
    shieldImage->attachTo(rootComponent);
    turnOffShield();

    auto thunderEvent = []()
    {
        MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
        if (mainLevel)
        {
            mainLevel->killAllEnemyAirplane();
        }
    };
    thunderAttack1 = new SpritesheetComponent("image/spritesheet/thunder.png",{0, 0},
                                             this,16,16,1);
    thunderAttack1->attachTo(rootComponent, false);
    thunderAttack1->setLooping(false);
    thunderAttack1->setDrawCntPerSec(15);
    thunderAttack1->setScale({700,Framework::rendererHeight});
    thunderAttack1->setComponentLocalLocation({-250.0f,0.0f});
    thunderAttack1->addEventAtNFrame(10, thunderEvent);

    thunderAttack2 = new SpritesheetComponent("image/spritesheet/thunder.png",{0, 0},
                                              this,16,16,1);
    thunderAttack2->attachTo(rootComponent, false);
    thunderAttack2->setLooping(false);
    thunderAttack2->setDrawCntPerSec(15);
    thunderAttack2->setScale({700,Framework::rendererHeight});
    thunderAttack2->setComponentLocalLocation({Framework::rendererWidth/2 - 350,0.0f});
    thunderAttack2->addEventAtNFrame(10, thunderEvent);

    thunderAttack3 = new SpritesheetComponent("image/spritesheet/thunder.png",{0, 0},
                                              this,16,16,1);
    thunderAttack3->attachTo(rootComponent, false);
    thunderAttack3->setLooping(false);
    thunderAttack3->setDrawCntPerSec(15);
    thunderAttack3->setScale({700,Framework::rendererHeight});
    thunderAttack3->setComponentLocalLocation({Framework::rendererWidth - 500,0.0f});
    thunderAttack3->addEventAtNFrame(10, thunderEvent);


}

Airplane::~Airplane()
{
    delete airplaneImg;
    airplaneImg = nullptr;

    delete boosterSprite;
    boosterSprite = nullptr;

    delete collisionBox;
    collisionBox = nullptr;

    delete explosionSprite;
    explosionSprite = nullptr;

    delete shieldImage;
    shieldImage = nullptr;

    delete thunderAttack1;
    thunderAttack1 = nullptr;

    delete thunderAttack2;
    thunderAttack2 = nullptr;

    delete thunderAttack3;
    thunderAttack3 = nullptr;

}

void Airplane::render()
{
    HPawn::render();
}

void Airplane::update(float deltaTime)
{
    HPawn::update(deltaTime);
    if(tickable)
    {
        curFireTime -= deltaTime;
        if (curFireTime <= 0.0f)
        {
            auto imageSize = airplaneImg->getScale();
            auto loc = rootComponent->getComponentLocalLocation();
            loc.first += float(imageSize.first) / 2 - float((bulletCnt - 1) * 20);
            spawnPlayerBullet(loc);
            curFireTime = fireRate;
        }
        if(!canDestroyable)
        {
            shieldAnimation(deltaTime);
            curShieldDuration-=deltaTime;
            if(curShieldDuration < 0.1f)
            {
                canDestroyable = true;
                turnOffShield();
            }
        }
    }
}

void Airplane::handleEvent(SDL_Event &e)
{
    if(canReceiveInputFromPlayer) //플레이어 입력을 받을 수 있을때만 동작하게 한다.
    {
        auto imageSize = airplaneImg->getScale();

        if (e.type == SDL_FINGERDOWN)
        {
            rootComponent->setComponentLocalLocation
                    (std::make_pair(
                            e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
                            e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
        }
        else if (e.type == SDL_FINGERMOTION)
        {
            rootComponent->setComponentLocalLocation
                    (std::make_pair(
                            e.tfinger.x * Framework::rendererWidth - float(imageSize.first) / 2,
                            e.tfinger.y * Framework::rendererHeight - float(imageSize.second) / 2));
        }
        else if (e.type == SDL_FINGERUP)
        {

        }
    }
}

CollisionBoxComponent* Airplane::getCollisionBoxComp()
{
    return collisionBox;
}

int Airplane::getPlayerAttackPower()
{
    return attackPower;
}

void Airplane::setFireRate(float rate)
{
    fireRate = rate;
}

void Airplane::setIsDie(bool isDie)
{
    this->isDie = isDie;
}

bool Airplane::getIsDie()
{
    return isDie;
}


void Airplane::setPlayerAttackPower(int attackPower)
{
    this->attackPower = attackPower;
}

int Airplane::getPlayerBulletCnt()
{
    return bulletCnt;
}

void Airplane::setPlayerBulletCnt(int bulletCnt)
{
    this->bulletCnt = bulletCnt;
}

int Airplane::getMissileCnt()
{
    return missileCnt;
}

void Airplane::setMissileCnt(int missileCnt)
{
    this->missileCnt = missileCnt;
}

int Airplane::getShieldCnt()
{
    return shieldCnt;
}

void Airplane::setShieldCnt(int shieldCnt)
{
    this->shieldCnt = shieldCnt;
}

PLAYER_AIRPLANE_SHAPE Airplane::getPlayerAirplaneShape()
{
    return shape;
}

void Airplane::setPlayerAirplaneShape(PLAYER_AIRPLANE_SHAPE shape)
{
    this->shape = shape;
    switch (this->shape)
    {
        case PLAYER_AIRPLANE_SHAPE::SHAPE2:
            airplaneImg->changeImage("image/player/2.png");
            airplaneImg->setScale({100, 115});
            break;

        case PLAYER_AIRPLANE_SHAPE::SHAPE3:
            airplaneImg->changeImage("image/player/3.png");
            airplaneImg->setScale({100, 115});
            break;
    }
}

void Airplane::enableShield()
{
    if(shieldCnt > 0 && !isDie)
    {
        turnOnShield();
        curShieldDuration = maxShieldDuration;
        canDestroyable = false;
        --shieldCnt;
    }
}


void Airplane::turnOffBooster()
{
    boosterSprite->setVisibility(false);
}

void Airplane::turnOnShield()
{
    shieldImage->setVisibility(true);
}

void Airplane::turnOffShield()
{
    shieldImage->setVisibility(false);
}


void Airplane::spawnPlayerBullet(std::pair<float, float>& spawnPos)
{
    if(!isDie)
    {
        MainLevel *mainLevel = Cast<MainLevel>(Framework::curLevel);
        auto cont = mainLevel->bulletPool;

        for(int i = bulletCnt; i > 0; --i)
        {
            auto bullet = cont->acquireObject();
            bullet->init(spawnPos, BULLET_COLOR::GREEN);
            bullet->setActorDirectionalVector({0.0f, -1.0f});
            bullet->changeBulletSpeed(1200.0f);
            spawnPos.first += 20.0f;
        }
    }
}

void Airplane::shieldAnimation(float deltaTime)
{
    shieldImage->setComponentLocalRotation(shieldRotation);
    shieldRotation+=50.0f*deltaTime;
    accTimeForFlickering += deltaTime;
    auto mT = fmod(accTimeForFlickering, 1.0) - 0.5f;
    shieldImage->setAlpha(int(fabs(mT * 2.0f)*255.0f));
}

void Airplane::enableThunder()
{
    if(missileCnt > 0 && !isDie)
    {
        thunderAttack1->play();
        thunderAttack2->play();
        thunderAttack3->play();

        --missileCnt;
    }
}

void Airplane::playerInitWhenStageBegin()
{
    airplaneImg->setVisibility(true);
    boosterSprite->setVisibility(true);
    isDie = false;
    canDestroyable = true;
    setVisibility(true);
    setActorTickable(true);
    explosionSprite->stop();
}
