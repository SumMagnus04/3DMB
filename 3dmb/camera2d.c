#include "camera2d.h"
#include "win.h"

Camera2D DMB_InitCamera2D(int screenWidth, int screenHeight)
{
	Camera2D camera;
	camera.position[0] = 0.0f;
	camera.position[1] = 0.0f;
	glm_mat4_identity(camera.cameraMatrix);
	glm_ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, 0.1, 1000.0, camera.orthoMatrix);
	camera.scale = 1;
	camera.screenWidth = screenWidth;
	camera.screenHeight = screenHeight;
	camera.needsUpdated = 1;
	return camera;
}

void DMB_SetPositionCamera2D(Camera2D* camera, vec2 newPosition)
{
	glm_vec2_copy(newPosition, camera->position);
	camera->needsUpdated = 1;
}

void DMB_SetScaleCamera2D(Camera2D* camera, float newScale)
{
	if (newScale < 0.1) newScale = 0.1;
	if (newScale > 10) newScale = 10;
	camera->scale = newScale;
	camera->needsUpdated = 1;
}

void DMB_UpdateCamera2D(Camera2D* camera)
{
	if (!camera->needsUpdated) return;

	vec3 translate;
	translate[0] = -camera->position[0] + camera->screenWidth / 2;
	translate[1] = -camera->position[1] + camera->screenHeight / 2;
	translate[2] = 0.0f;
	glm_translate_to(camera->orthoMatrix, translate, camera->cameraMatrix);

	vec3 scale;
	scale[0] = camera->scale;
	scale[1] = camera->scale;
	scale[2] = 0.0f;
	mat4 identity;
	glm_mat4_identity(identity);
	glm_scale(identity, scale);
	mat4 mul;
	glm_mat4_mul(identity, camera->cameraMatrix, mul);
	glm_mat4_copy(mul, camera->cameraMatrix);

	camera->needsUpdated = 0;
}

void DMB_SetMouseToCamera(Camera2D* camera, Mouse* mouse, vec2 cameraCoords)
{
	cameraCoords[0] = mouse->x - DMB_SCREEN_WIDTH / 2.0f;
	cameraCoords[1] = DMB_SCREEN_HEIGHT - mouse->y;
	cameraCoords[1] -= DMB_SCREEN_HEIGHT / 2.0f;
	cameraCoords[0] /= camera->scale;
	cameraCoords[1] /= camera->scale;
	cameraCoords[0] += camera->position[0];
	cameraCoords[1] += camera->position[1];
}