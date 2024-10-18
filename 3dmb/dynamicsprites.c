#include "dynamicsprites.h"
#include <stdlib.h>
#include "errors.h"

void dynamicInitSprite(SpriteArray* arr, Sprite firstSprite)
{
	arr->sprites = (Sprite*)malloc(sizeof(Sprite));
	if (arr->sprites == NULL)
	{
		fatalError("Failed to initialize SpriteArray.");
		return;
	}
	arr->sprites = &firstSprite;
	arr->size = 1;
}

void dynamicAddSprite(SpriteArray* arr, Sprite sprite)
{
	arr->size++;
	Sprite* a = (Sprite*)malloc(arr->size * sizeof(Sprite));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: SpriteArray Add");
		return;
	}
	for (int i = 0; i < arr->size - 1; i++) a[i] = arr->sprites[i];
	a[arr->size - 1] = sprite;
	arr->sprites = a;
}

void dynamicRemoveSprite(SpriteArray* arr, unsigned int index)
{
	if (index >= arr->size) return;
	Sprite* a = (Sprite*)malloc((arr->size - 1) * sizeof(Sprite));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: SpriteArray Remove");
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
		a[i - off] = arr->sprites[i];
	}
	arr->size--;
	arr->sprites = a;
}