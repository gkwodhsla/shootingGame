#include "Bullet.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Components/MovementComponent.h"

Bullet::Bullet(const std::pair<int, int> &spawnPosition, BULLET_COLOR bulletColor,
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
}

Bullet::~Bullet()
{
    delete rootComponent;
    rootComponent = nullptr;

    delete bulletImg;
    bulletImg = nullptr;
}

void Bullet::render()
{

}

void Bullet::update(float deltaTime)
{

}
