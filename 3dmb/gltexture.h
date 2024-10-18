#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

typedef struct GLTexture
{
	GLuint id;
	int width;
	int height;
} GLTexture;

GLTexture loadPng(const char* filePath);

#endif