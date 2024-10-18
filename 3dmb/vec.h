#ifndef VEC_H
#define VEC_H

#include <GL/glew.h>

typedef struct Position
{
	float x;
	float y;
} Position;

typedef struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
} Color;

typedef struct UV
{
	float u;
	float v;
} UV;

typedef struct Vertex
{
	Position position;
	Color color;
	UV uv;
} Vertex;

extern void setPosition(Vertex* vertex, float x, float y);
extern void setColor(Vertex* vertex, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
extern void setUV(Vertex* vertex, float u, float v);

#endif