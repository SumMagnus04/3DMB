#ifndef WIN_H
#define WIN_H

#include <SDL/SDL.h>

int DMB_SCREEN_WIDTH;
int DMB_SCREEN_HEIGHT;

enum WindowFlags
{
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

SDL_Window* DMB_WINDOW;

int DMB_CreateWindow(const char* name, int screenWidth, int screenHeight, unsigned int currentFlags);

#endif