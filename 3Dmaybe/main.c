#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <cglm/cglm.h>
#include <3dmb/3dmb.h>

#include "bullet.h"

#define MAX_FPS 60
#define MAX_BULLETS 100
Bullet bullets[MAX_BULLETS];

int handleInput(int* keys, Camera2D* camera, Mouse* mouse);

enum GameState
{
	PLAY,
	EXIT
};

int main(int argc, char** argv)
{
	DMB_Init();

	DMB_CreateWindow("3Dmaybe", 640, 480, 0);

	Camera2D camera = DMB_InitCamera2D(DMB_SCREEN_WIDTH, DMB_SCREEN_HEIGHT);
	Mouse mouse = DMB_InitMouse();

	GLSLProgram colorProgram;
	colorProgram.numAttributes = 0;
	DMB_CompileShaders(&colorProgram, "shaders/ColorShader.vert.glsl", "shaders/ColorShader.frag.glsl");
	DMB_AddAttribute(&colorProgram, "vertexPosition");
	DMB_AddAttribute(&colorProgram, "vertexColor");
	DMB_AddAttribute(&colorProgram, "vertexUV");
	DMB_LinkShaders(&colorProgram);

	TextureArray textures;
	dynamicInitTexture(&textures, loadPng("textures/PNG/CharacterRight_Standing.png"));

	SpriteBatch spriteBatch;
	initSpriteBatch(&spriteBatch);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		vec2 position;
		position[0] = 0.0f;
		position[1] = 0.0f;
		bullets[i] = initBullet(position, position, 0.0f, 0);
	}

	enum GameState gameState = PLAY;

	FPSData fpsData = initFPSLimiter(MAX_FPS);

	int keys[DMB_NUM_KEYS];
	for (int i = 0; i < DMB_NUM_KEYS; i++) keys[i] = 0;

	while (gameState != EXIT)
	{
		beginFPSLimiter(&fpsData);

		gameState = handleInput(keys, &camera, &mouse);
		updateCamera2D(&camera);

		for (int i = 0; i < MAX_BULLETS; i++)
			if (bullets[i].lifeTime > 0) updateBullet(&bullets[i]);

		// DRAW GAME
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DMB_UseGLSLProgram(&colorProgram);

		glActiveTexture(GL_TEXTURE0);

		GLint texLocation = DMB_GetUniformLocation(&colorProgram, "tex");
		glUniform1i(texLocation, 0);

		GLint pLocation = DMB_GetUniformLocation(&colorProgram, "P");
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, camera.cameraMatrix[0]);

		beginSpriteBatch(&spriteBatch, BY_TEXTURE);

		vec4 position;
		position[0] = 0.0f;
		position[1] = 0.0f;
		position[2] = 50.0f;
		position[3] = 50.0f;
		vec4 uv;
		uv[0] = 0.0f;
		uv[1] = 0.0f;
		uv[2] = 1.0f;
		uv[3] = 1.0f;
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		drawSpriteBatch(&spriteBatch, position, uv, textures.textures[0].id, 0.0f, &color);

		for (int i = 0; i < MAX_BULLETS; i++)
			if (bullets[i].lifeTime > 0)
				drawBullet(&bullets[i], &spriteBatch, textures.textures[0].id);

		endSpriteBatch(&spriteBatch);
		renderSpriteBatch(&spriteBatch);

		glBindTexture(GL_TEXTURE_2D, 0);

		DMB_UnuseGLSLProgram(&colorProgram);

		SDL_GL_SwapWindow(DMB_WINDOW);
		
		// END DRAW GAME

		endFPSLimiter(&fpsData);
	}

	return 0;
}

int handleInput(int* keys, Camera2D* camera, Mouse* mouse)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: return EXIT; break;
		case SDL_KEYDOWN: DMB_KeyDown(event.key.keysym.sym, keys, mouse); break;
		case SDL_KEYUP: DMB_KeyUp(event.key.keysym.sym, keys, mouse); break;
		case SDL_MOUSEBUTTONDOWN: DMB_KeyDown(event.button.button, keys, mouse);  break;
		case SDL_MOUSEBUTTONUP: DMB_KeyUp(event.button.button, keys, mouse); break;
		case SDL_MOUSEMOTION: DMB_SetMouseCoords(mouse, event.motion.x, event.motion.y);  break;
		}
	}

	if (keys[K_W])
	{
		vec2 newPosition;
		vec2 move;
		move[0] = 0.0f;
		move[1] = 5.0f;
		glm_vec2_add(camera->position, move, newPosition);
		DMB_SetPositionCamera2D(camera, newPosition);
	}

	if (keys[K_S])
	{
		vec2 newPosition;
		vec2 move;
		move[0] = 0.0f;
		move[1] = -5.0f;
		glm_vec2_add(camera->position, move, newPosition);
		DMB_SetPositionCamera2D(camera, newPosition);
	}

	if (keys[K_A])
	{
		vec2 newPosition;
		vec2 move;
		move[0] = -5.0f;
		move[1] = 0.0f;
		glm_vec2_add(camera->position, move, newPosition);
		DMB_SetPositionCamera2D(camera, newPosition);
	}

	if (keys[K_D])
	{
		vec2 newPosition;
		vec2 move;
		move[0] = 5.0f;
		move[1] = 0.0f;
		glm_vec2_add(camera->position, move, newPosition);
		DMB_SetPositionCamera2D(camera, newPosition);
	}

	if (keys[K_E]) DMB_SetScaleCamera2D(camera, camera->scale + 0.05f);
	if (keys[K_Q]) DMB_SetScaleCamera2D(camera, camera->scale - 0.05f);

	if (mouse->buttonLeft)
	{
		vec2 mouseCameraCoords;
		DMB_SetMouseToCamera(camera, mouse, mouseCameraCoords);

		vec2 playerPosition;
		playerPosition[0] = 0.0f;
		playerPosition[1] = 0.0f;

		vec2 direction;
		direction[0] = mouseCameraCoords[0] - playerPosition[0];
		direction[1] = mouseCameraCoords[1] - playerPosition[1];
		glm_vec2_normalize(direction);

		for (int i = 0; i < MAX_BULLETS; i++)
			if (bullets[i].lifeTime <= 0)
			{
				bullets[i] = initBullet(playerPosition, direction, 5.0f, 500);
				break;
			}
	}

	return PLAY;
}