#include "errors.h"
#include <SDL/SDL.h>

void fatalError(const char* error)
{
	printf("%s\nEnter any key to quit...", error);
	int temp = getchar();
	SDL_Quit();
	exit(4269);
}