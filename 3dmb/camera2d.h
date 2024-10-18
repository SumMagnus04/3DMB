#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <cglm/cglm.h>
#include "input.h"

typedef struct Camera2D
{
	vec2 position;
	mat4 cameraMatrix;
	mat4 orthoMatrix;
	float scale;
	int screenWidth;
	int screenHeight;
	unsigned int needsUpdated;
} Camera2D;

Camera2D DMB_InitCamera2D(int screenWidth, int screenHeight);
void DMB_SetPositionCamera2D(Camera2D* camera, vec2 newPosition);
void DMB_SetScaleCamera2D(Camera2D* camera, float newScale);
void DMB_UpdateCamera2D(Camera2D* camera);

void DMB_SetMouseToCamera(Camera2D* camera, Mouse* mouse, vec2 cameraCoords);

#endif