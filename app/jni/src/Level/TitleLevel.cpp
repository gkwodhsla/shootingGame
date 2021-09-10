#include "TitleLevel.h"
#include "../TitleController.h"

TitleLevel::TitleLevel()
{
    setID(GlobalFunction::GetClassTypeUniqueID<TitleLevel>());
}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::handleEvent(const SDL_Event &e)
{
    HLevelBase::handleEvent(e);

}

void TitleLevel::update(float deltaTime)
{
    HLevelBase::update(deltaTime);
}

void TitleLevel::render()
{
    HLevelBase::render();
}

void TitleLevel::enter()
{
    playerController = new TitleController(nullptr);
}

void TitleLevel::exit()
{

}
