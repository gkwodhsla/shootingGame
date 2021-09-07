#include "TitleLevel.h"
#include "../TitleController.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::handleEvent(SDL_Event &e)
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
