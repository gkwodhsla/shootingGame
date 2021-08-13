#include "EnemyAirplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/HSceneComponent.h"

EnemyAirplane::EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape):bulletColor(color)
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

    rootComponent->setOwner(this);
    rootComponent->setComponentLocalLocation(std::make_pair(0, 0));
    rootComponent->setComponentLocalRotation(0);


    //hpBar = new ImageComponent()
}

EnemyAirplane::~EnemyAirplane()
{

}

void EnemyAirplane::render()
{
    Airplane::render();
}

void EnemyAirplane::update(float deltaTime)
{
    Airplane::update(deltaTime);
}

void EnemyAirplane::handleEvent(SDL_Event &e)
{
    Airplane::handleEvent(e);
}
