#include "AirplaneParent.h"
#include "../Components/ImageComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/AudioComponent.h"

AirplaneParent::AirplaneParent()
{
    explosionSprite = createComponent<SpritesheetComponent>("image/spritesheet/explosion.png",
                                               std::make_pair(-80.0f, -45.0f), this, 24, 6, 4);
    explosionSprite->attachTo(rootComponent);
    explosionSprite->setScale(std::make_pair(350, 350));
    explosionSprite->setLooping(false);
    explosionSprite->setDrawCntPerSec(40);

    collisionBox = createComponent<CollisionBoxComponent>(0, 0, 100, 100, this);
    //collisionBox->setDrawDebugBox(true);
    collisionBox->attachTo(rootComponent);

    explosionAudio = createComponent<AudioComponent>("sound/explosion.wav", 180, this);
}

AirplaneParent::~AirplaneParent()
{

}

void AirplaneParent::render()
{
    HPawn::render();
}

void AirplaneParent::update(const float deltaTime)
{
    HPawn::update(deltaTime);
}

void AirplaneParent::handleEvent(const SDL_Event& e)
{

}

void AirplaneParent::setIsDie(bool isDie)
{
    this->isDie = isDie;
}

bool AirplaneParent::getIsDie()
{
    return isDie;
}

void AirplaneParent::setFireRate(float rate)
{
    fireRate = rate;
}