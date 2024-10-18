#ifndef TIMING_H
#define TIMING_H

typedef struct FPSData
{
	int targetFPS;
	unsigned int startTicks;
	unsigned int currentTime;
	unsigned int fps;
} FPSData;

FPSData initFPSLimiter(int targetFPS);
void beginFPSLimiter(FPSData* fpsData);
int endFPSLimiter(FPSData* fpsData);

#endif
