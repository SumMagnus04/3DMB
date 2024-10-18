#ifndef DYNAMICTEXTURES_H
#define DYNAMICTEXTURES_H

#include "gltexture.h"

typedef struct DynamicTextureArray
{
	GLTexture* textures;
	unsigned int size;
} TextureArray;

void dynamicInitTexture(TextureArray* arr, GLTexture firstTexture);
void dynamicAddTexture(TextureArray* arr, GLTexture texture);
void dynamicRemoveTexture(TextureArray* arr, unsigned int index);

#endif