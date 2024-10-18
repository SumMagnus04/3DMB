#include "timing.h"
#include <stdio.h>
#include <SDL/SDL.h>

void calculateFPS(unsigned int* currentTime, unsigned int* fps)
{
	(*fps)++;
	if (SDL_GetTicks() - *currentTime >= 1000)
	{
		printf("%d\n", *fps - 1);
		*fps = 0;
		*currentTime = SDL_GetTicks();
	}
}

FPSData initFPSLimiter(int targetFPS)
{
	FPSData fpsData;
	fpsData.targetFPS = targetFPS;
	return fpsData;
}

void beginFPSLimiter(FPSData* fpsData)
{
	fpsData->startTicks = SDL_GetTicks();
}

int endFPSLimiter(FPSData* fpsData)
{
	calculateFPS(&fpsData->currentTime, &fpsData->fps);
	unsigned int frameTicks = SDL_GetTicks() - fpsData->startTicks;
	if (1000 / fpsData->targetFPS > frameTicks) SDL_Delay(1000 / fpsData->targetFPS - frameTicks);
}