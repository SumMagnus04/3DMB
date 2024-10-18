#include "dynamictextures.h"
#include <stdlib.h>

void dynamicInitTexture(TextureArray* arr, GLTexture firstTexture)
{
	arr->textures = (GLTexture*)malloc(sizeof(GLTexture));
	if (arr->textures == NULL)
	{
		fatalError("Failed to initialize TextureArray.");
		return;
	}
	arr->textures = &firstTexture;
	arr->size = 1;
}

void dynamicAddTexture(TextureArray* arr, GLTexture texture)
{
	arr->size++;
	GLTexture* a = (GLTexture*)malloc(arr->size * sizeof(GLTexture));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: TextureArray Add");
		return;
	}
	for (int i = 0; i < arr->size - 1; i++) a[i] = arr->textures[i];
	a[arr->size - 1] = texture;
	arr->textures = a;
}

void dynamicRemoveTexture(TextureArray* arr, unsigned int index)
{
	if (index >= arr->size) return;
	GLTexture* a = (GLTexture*)malloc((arr->size - 1) * sizeof(GLTexture));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: TextureArray Remove");
		return;
	}
	unsigned int off = 0;
	for (unsigned int i = 0; i < arr->size; i++)
	{
		if (i == index)
		{
			off++;
			continue;
		}
		a[i - off] = arr->textures[i];
	}
	arr->size--;
	arr->textures = a;
}