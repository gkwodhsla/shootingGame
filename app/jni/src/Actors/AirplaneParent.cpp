#include "AirplaneParent.h"
#include "../Components/ImageComponent.h"
#include "../Components/SpritesheetComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/AudioComponent.h"

AirplaneParent::AirplaneParent()
{
    explosionSprite = new SpritesheetComponent("image/spritesheet/explosion.png",
                                               std::make_pair(-80.0f, -45.0f), this, 24, 6, 4);
    explosionSprite->attachTo(rootComponent);
    explosionSprite->setScale(std::make_pair(350, 350));
    explosionSprite->setLooping(false);
    explosionSprite->setDrawCntPerSec(40);

    collisionBox = new CollisionBoxComponent(0, 0, 100, 100, this);
    collisionBox->setDrawDebugBox(true);
    collisionBox->attachTo(rootComponent);

    explosionAudio = new AudioComponent("sound/explosion.wav", 180, this);
}

AirplaneParent::~AirplaneParent()
{
    delete airplaneImg;
    airplaneImg = nullptr;

    delete collisionBox;
    collisionBox = nullptr;

    delete explosionSprite;
    explosionSprite = nullptr;

    delete explosionAudio;
    explosionAudio = nullptr;
}

void AirplaneParent::render()
{
    HPawn::render();
}

void AirplaneParent::update(float deltaTime)
{
    HPawn::update(deltaTime);
}

void AirplaneParent::handleEvent(SDL_Event& e)
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