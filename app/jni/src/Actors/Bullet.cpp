#include "Bullet.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Components/MovementComponent.h"
#include <android/log.h>
Bullet::Bullet(const std::pair<float, float> &spawnPosition, BULLET_COLOR bulletColor,
               const std::pair<float, float>& dirVec)
{
    rootComponent = new HSceneComponent();
    rootComponent->setComponentLocalLocation(spawnPosition);
    rootComponent->setComponentLocalRotation(0.0f);
    std::string path;
    if(bulletColor == BULLET_COLOR::GREEN)
    {
        path = "image/bullet/1.png";
    }
    else if(bulletColor == BULLET_COLOR::RED)
    {
        path = "image/bullet/2.png";
    }
    else if(bulletColor == BULLET_COLOR::PURPLE)
    {
        path = "image/bullet/3.png";
    }
    bulletImg = new ImageComponent(path, std::make_pair(0, 0), this);

    bulletImg->attachTo(rootComponent);

    bulletMovement = new MovementComponent(this);
    this->dirVec = dirVec;

    bulletMovement->setInitialVelocity(std::make_pair(dirVec.first * 900.0f, dirVec.second * 900.0f));
    bulletMovement->setAcceleration(std::make_pair(dirVec.first * 1000.0f, dirVec.second * 1000.0f));
}

Bullet::~Bullet()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete bulletImg;
    bulletImg = nullptr;

    delete bulletMovement;
    bulletMovement = nullptr;
}

void Bullet::render()
{
    HActor::render();
}

void Bullet::update(float deltaTime)
{
    HActor::update(deltaTime);
    if(tickable)
    {
        bulletMovement->update(deltaTime);
        if(isPendingToKill)
        {
            tickable = false;
            visibility = false;
            lifeTime = 3.0f;
            isPendingToKill = false;
            __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                                "bullet pending kill success");
        }
    }
}
