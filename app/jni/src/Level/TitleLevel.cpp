#include "TitleLevel.h"
#include "../TitleController.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::handleEvent(const SDL_Event &e)
{
    HLevelBase::handleEvent(e);

}

void TitleLevel::update(const float deltaTime)
{
    HLevelBase::update(deltaTime);
}

void TitleLevel::render()
{
    HLevelBase::render();
}

void TitleLevel::enter()
{
    playerController = GlobalFunction::createNewObject<TitleController>(nullptr);
}

void TitleLevel::exit()
{

}
