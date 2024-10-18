#include "sprite.h"
#include "vec.h"
#include <stdlib.h>

Sprite initSprite(float x, float y, float width, float height, unsigned int texture)
{
	Sprite s;
	s.x = x;
	s.y = y;
	s.width = width;
	s.height = height;
	s.texture = texture;

	glGenBuffers(1, &s.vboID);

	Vertex vertexData[6];

	setPosition(&vertexData[0], x + width, y + height);
	setUV(&vertexData[0], 1.0f, 1.0f);

	setPosition(&vertexData[1], x, y + height);
	setUV(&vertexData[1], 0.0f, 1.0f);

	setPosition(&vertexData[2], x, y);
	setUV(&vertexData[2], 0.0f, 0.0f);

	setPosition(&vertexData[3], x, y);
	setUV(&vertexData[3], 0.0f, 0.0f);

	setPosition(&vertexData[4], x + width, y);
	setUV(&vertexData[4], 1.0f, 0.0f);

	setPosition(&vertexData[5], x + width, y + height);
	setUV(&vertexData[5], 1.0f, 1.0f);

	for (int i = 0; i < 6; i++) setColor(&vertexData[i], 255, 0, 255, 255);
	setColor(&vertexData[1], 0, 0, 255, 255);
	setColor(&vertexData[4], 0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, s.vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return s;
}

void drawSprite(Sprite* s, TextureArray textures)
{
	glBindTexture(GL_TEXTURE_2D, textures.textures[s->texture].id);

	glBindBuffer(GL_ARRAY_BUFFER, s->vboID);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void destroySprite(Sprite* s)
{
	if (s->vboID != 0) glDeleteBuffers(1, s->vboID);
}