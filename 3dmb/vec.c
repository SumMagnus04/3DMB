#include "vec.h"

void setPosition(Vertex* vertex, float x, float y)
{
	vertex->position.x = x;
	vertex->position.y = y;
}

void setColor(Vertex* vertex, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	vertex->color.r = r;
	vertex->color.g = g;
	vertex->color.b = b;
	vertex->color.a = a;
}

void setUV(Vertex* vertex, float u, float v)
{
	vertex->uv.u = u;
	vertex->uv.v = v;
}