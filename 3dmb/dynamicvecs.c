#include "dynamicvecs.h"
#include <stdlib.h>
#include "errors.h"

void dynamicInitVertex(VertexArray* arr, Vertex firstVertex)
{
	arr->vertices = (Vertex*)malloc(sizeof(Vertex));
	if (arr->vertices == NULL)
	{
		fatalError("Failed to initialize VertexArray.");
		return;
	}
	arr->vertices = &firstVertex;
	arr->size = 1;
}

void dynamicAddVertex(VertexArray* arr, Vertex vertex)
{
	arr->size++;
	Vertex* a = (Vertex*)malloc(arr->size * sizeof(Vertex));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: VertexArray Add");
		return;
	}
	for (int i = 0; i < arr->size - 1; i++) a[i] = arr->vertices[i];
	a[arr->size - 1] = vertex;
	arr->vertices = a;
}

void dynamicRemoveVertex(VertexArray* arr, unsigned int index)
{
	if (index >= arr->size) return;
	Vertex* a = (Vertex*)malloc((arr->size - 1) * sizeof(Vertex));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: VertexArray Remove");
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
		a[i - off] = arr->vertices[i];
	}
	arr->size--;
	arr->vertices = a;
}