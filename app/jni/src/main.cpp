#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <android/log.h>
#include "Framework.h"
#include "Components/ImageComponent.h"

int main( int argc, char* args[] )
{
    Framework* game = Framework::getInstance();
    game->startGame();

    delete game;
    game = nullptr;

    return 0;
}