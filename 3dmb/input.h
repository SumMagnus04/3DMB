#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#define DMB_NUM_KEYS 45

enum Keys
{
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_TAB,
	K_LSHIFT,
	K_RSHIFT,
	K_LCTRL,
	K_RCTRL
};

typedef struct Mouse
{
	float x;
	float y;
	int buttonLeft;
	int buttonRight;
} Mouse;

void DMB_KeyDown(int sdl_key, int* keys, Mouse* mouse);
void DMB_KeyUp(int sdl_key, int* keys, Mouse* mouse);

Mouse DMB_InitMouse();
void DMB_SetMouseCoords(Mouse* mouse, float x, float y);

#endif
