#ifndef DYNAMICVECS_H
#define DYNAMICVECS_H

#include "vec.h"

typedef struct DynamicVertexArray
{
	Vertex* vertices;
	unsigned int size;
} VertexArray;

void dynamicInitVertex(VertexArray* arr, Vertex firstVertex);
void dynamicAddVertex(VertexArray* arr, Vertex vertex);
void dynamicRemoveVertex(VertexArray* arr, unsigned int index);

#endif