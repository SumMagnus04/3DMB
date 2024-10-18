#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "dynamictextures.h"

typedef struct Sprite
{
	float x;
	float y;
	float width;
	float height;
	GLuint vboID;
	unsigned int texture;
} Sprite;

Sprite initSprite(float x, float y, float width, float height, unsigned int texture);
void drawSprite(Sprite* s, TextureArray textures);
void destroySprite(Sprite* s);

#endif