/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <android/log.h>
#include "Framework.h"

int main( int argc, char* args[] )
{

    Framework game;

    game.startGame();

	return 0;
}