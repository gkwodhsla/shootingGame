#include "Crystal.h"
#include "Airplane.h"
#include "../Components/ImageComponent.h"
#include "../Components/CollisionBoxComponent.h"
#include "../Components/MovementComponent.h"
#include "../GlobalFunction.h"
#include "../Level/MainLevel.h"
#include "../ActorObjectPool.h"
#include "../UI/ShopCanvas.h"
#include "../AirplaneController.h"
#include <android/log.h>

using namespace GlobalFunction;

const float Crystal::destroyDistance = 2500.0f;

Crystal::Crystal()
{
    crystalImg = createComponent<ImageComponent>("image/UIImage/crystal.png", std::make_pair(0,0), this);
    crystalImg->setScale({70, 70});
    crystalImg->attachTo(rootComponent);

    auto crystalImgSize = crystalImg->getScale();
    collisionBox = createComponent<CollisionBoxComponent>(0, 0, crystalImgSize.first, crystalImgSize.second,
                                             this);
    collisionBox->attachTo(rootComponent);
    auto collisionFunc = [=](HActor* other)
    {
        if(other == GetPlayerPawn())
        {
            auto mainLevel = Cast<MainLevel>(GetLevel());
            auto PC = Cast<AirplaneController>(GetPlayerController());
            auto playerAirplane = Cast<Airplane>(other);
            if(mainLevel && !playerAirplane->getIsDie())
            {
                mainLevel->crystalPool->returnToPool(this);
                auto canvas = Cast<ShopCanvas>(PC->shopCanvas);
                if(canvas)
                {
                    canvas->addCrystal(1);
                }
                playerAirplane->playCoinSound();
            }
        }
    };
    collisionBox->registerCollisionResponse(collisionFunc);
    //collisionBox->setDrawDebugBox(true);

    crystalMovement = createComponent<MovementComponent>(this);
    crystalMovement->setSpeed(500.0f);

    dirVec = Vector2D({0.0f, 1.0f});
}

Crystal::~Crystal()
{

}

void Crystal::render()
{
    HActor::render();
}

void Crystal::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(tickable)
    {
        crystalMovement->update(deltaTime);
        if(rootComponent->getComponentWorldLocation().second > destroyDistance)
        {
            auto mainLevel = Cast<MainLevel>(GetLevel());
            if(mainLevel)
            {
                mainLevel->crystalPool->returnToPool(this);
            }
        }
    }
}
