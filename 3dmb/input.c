#include "input.h"
#include <stdio.h>

void DMB_KeyDown(int sdl_key, int* keys, Mouse* mouse)
{
	switch (sdl_key)
	{
	case SDLK_a: keys[K_A] = 1; break;
	case SDLK_b: keys[K_B] = 1; break;
	case SDLK_c: keys[K_C] = 1; break;
	case SDLK_d: keys[K_D] = 1; break;
	case SDLK_e: keys[K_E] = 1; break;
	case SDLK_f: keys[K_F] = 1; break;
	case SDLK_g: keys[K_G] = 1; break;
	case SDLK_h: keys[K_H] = 1; break;
	case SDLK_i: keys[K_I] = 1; break;
	case SDLK_j: keys[K_J] = 1; break;
	case SDLK_k: keys[K_K] = 1; break;
	case SDLK_l: keys[K_L] = 1; break;
	case SDLK_m: keys[K_M] = 1; break;
	case SDLK_n: keys[K_N] = 1; break;
	case SDLK_o: keys[K_O] = 1; break;
	case SDLK_p: keys[K_P] = 1; break;
	case SDLK_q: keys[K_Q] = 1; break;
	case SDLK_r: keys[K_R] = 1; break;
	case SDLK_s: keys[K_S] = 1; break;
	case SDLK_t: keys[K_T] = 1; break;
	case SDLK_u: keys[K_U] = 1; break;
	case SDLK_v: keys[K_V] = 1; break;
	case SDLK_w: keys[K_W] = 1; break;
	case SDLK_x: keys[K_X] = 1; break;
	case SDLK_y: keys[K_Y] = 1; break;
	case SDLK_z: keys[K_Z] = 1; break;
	case SDLK_1: keys[K_1] = 1; break;
	case SDLK_2: keys[K_2] = 1; break;
	case SDLK_3: keys[K_3] = 1; break;
	case SDLK_4: keys[K_4] = 1; break;
	case SDLK_5: keys[K_5] = 1; break;
	case SDLK_6: keys[K_6] = 1; break;
	case SDLK_7: keys[K_7] = 1; break;
	case SDLK_8: keys[K_8] = 1; break;
	case SDLK_9: keys[K_9] = 1; break;
	case SDLK_0: keys[K_0] = 1; break;
	case SDLK_UP: keys[K_UP] = 1; break;
	case SDLK_DOWN: keys[K_DOWN] = 1; break;
	case SDLK_LEFT: keys[K_LEFT] = 1; break;
	case SDLK_RIGHT: keys[K_RIGHT] = 1; break;
	case SDLK_TAB: keys[K_TAB] = 1; break;
	case SDLK_LSHIFT: keys[K_LSHIFT] = 1; break;
	case SDLK_RSHIFT: keys[K_RSHIFT] = 1; break;
	case SDLK_LCTRL: keys[K_LCTRL] = 1; break;
	case SDLK_RCTRL: keys[K_RCTRL] = 1; break;
	case SDL_BUTTON_LEFT: mouse->buttonLeft = 1; break;
	case SDL_BUTTON_RIGHT: mouse->buttonRight = 1; break;
	}
}

void DMB_KeyUp(int sdl_key, int* keys, Mouse* mouse)
{
	switch (sdl_key)
	{
	case SDLK_a: keys[K_A] = 0; break;
	case SDLK_b: keys[K_B] = 0; break;
	case SDLK_c: keys[K_C] = 0; break;
	case SDLK_d: keys[K_D] = 0; break;
	case SDLK_e: keys[K_E] = 0; break;
	case SDLK_f: keys[K_F] = 0; break;
	case SDLK_g: keys[K_G] = 0; break;
	case SDLK_h: keys[K_H] = 0; break;
	case SDLK_i: keys[K_I] = 0; break;
	case SDLK_j: keys[K_J] = 0; break;
	case SDLK_k: keys[K_K] = 0; break;
	case SDLK_l: keys[K_L] = 0; break;
	case SDLK_m: keys[K_M] = 0; break;
	case SDLK_n: keys[K_N] = 0; break;
	case SDLK_o: keys[K_O] = 0; break;
	case SDLK_p: keys[K_P] = 0; break;
	case SDLK_q: keys[K_Q] = 0; break;
	case SDLK_r: keys[K_R] = 0; break;
	case SDLK_s: keys[K_S] = 0; break;
	case SDLK_t: keys[K_T] = 0; break;
	case SDLK_u: keys[K_U] = 0; break;
	case SDLK_v: keys[K_V] = 0; break;
	case SDLK_w: keys[K_W] = 0; break;
	case SDLK_x: keys[K_X] = 0; break;
	case SDLK_y: keys[K_Y] = 0; break;
	case SDLK_z: keys[K_Z] = 0; break;
	case SDLK_1: keys[K_1] = 0; break;
	case SDLK_2: keys[K_2] = 0; break;
	case SDLK_3: keys[K_3] = 0; break;
	case SDLK_4: keys[K_4] = 0; break;
	case SDLK_5: keys[K_5] = 0; break;
	case SDLK_6: keys[K_6] = 0; break;
	case SDLK_7: keys[K_7] = 0; break;
	case SDLK_8: keys[K_8] = 0; break;
	case SDLK_9: keys[K_9] = 0; break;
	case SDLK_0: keys[K_0] = 0; break;
	case SDLK_UP: keys[K_UP] = 0; break;
	case SDLK_DOWN: keys[K_DOWN] = 0; break;
	case SDLK_LEFT: keys[K_LEFT] = 0; break;
	case SDLK_RIGHT: keys[K_RIGHT] = 0; break;
	case SDLK_TAB: keys[K_TAB] = 0; break;
	case SDLK_LSHIFT: keys[K_LSHIFT] = 0; break;
	case SDLK_RSHIFT: keys[K_RSHIFT] = 0; break;
	case SDLK_LCTRL: keys[K_LCTRL] = 0; break;
	case SDLK_RCTRL: keys[K_RCTRL] = 0; break;
	case SDL_BUTTON_LEFT: mouse->buttonLeft = 0; break;
	case SDL_BUTTON_RIGHT: mouse->buttonRight = 0; break;
	}
}

Mouse DMB_InitMouse()
{
	Mouse mouse;
	mouse.x = 0.0f;
	mouse.y = 0.0f;
	mouse.buttonLeft = 0;
	mouse.buttonRight = 0;
	return mouse;
}

void DMB_SetMouseCoords(Mouse* mouse, float x, float y)
{
	mouse->x = x;
	mouse->y = y;
}