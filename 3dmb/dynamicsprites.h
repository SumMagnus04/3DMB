#ifndef DYNAMICSPRITES_H
#define DYNAMICSPRITES_H

#include "sprite.h"

typedef struct DynamicSpriteArray
{
	Sprite* sprites;
	unsigned int size;
} SpriteArray;

void dynamicInitSprite(SpriteArray* arr, Sprite firstSprite);
void dynamicAddSprite(SpriteArray* arr, Sprite sprite);
void dynamicRemoveSprite(SpriteArray* arr, unsigned int index);

#endif