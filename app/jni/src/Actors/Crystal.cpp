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

Crystal::Crystal() {
    crystalImg = new ImageComponent("image/UIImage/crystal.png", {0, 0}, this);
    crystalImg->setScale({70, 70});
    crystalImg->attachTo(rootComponent);

    auto crystalImgSize = crystalImg->getScale();
    collisionBox = new CollisionBoxComponent(0, 0, crystalImgSize.first, crystalImgSize.second,
                                             this);
    collisionBox->attachTo(rootComponent);
    auto collisionFunc = [=](HActor* other)
    {
        if(other == GetPlayerPawn())
        {
            auto mainLevel = Cast<MainLevel>(GetLevel());
            auto PC = Cast<AirplaneController>(GetPlayerController());
            if(mainLevel)
            {
                mainLevel->crystalPool->returnToPool(this);
                auto canvas = Cast<ShopCanvas>(PC->shopCanvas);
                if(canvas)
                {
                    canvas->addCrystal(1);
                }
            }
        }
    };
    collisionBox->registerCollisionResponse(collisionFunc);
    collisionBox->setDrawDebugBox(true);

    crystalMovement = new MovementComponent(this);
    crystalMovement->setSpeed(300.0f);

    dirVec = Vector2D({0.0f, 1.0f});
}

Crystal::~Crystal()
{
    delete crystalImg;
    crystalImg = nullptr;

    delete collisionBox;
    collisionBox = nullptr;

    delete crystalMovement;
    crystalMovement = nullptr;
}

void Crystal::render()
{
    HActor::render();
}

void Crystal::update(float deltaTime)
{
    HActor::update(deltaTime);
    if(tickable)
    {
        crystalMovement->update(deltaTime);
        if(rootComponent->getComponentWorldLocation().second > 2500.0f)
        {
            auto mainLevel = Cast<MainLevel>(GetLevel());
            if(mainLevel)
            {
                mainLevel->crystalPool->returnToPool(this);
            }
        }
    }
}
