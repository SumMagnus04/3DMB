#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <cglm/cglm.h>
#include "vec.h"

typedef enum GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	BY_TEXTURE
} GlyphSortType;

typedef struct Glyph
{
	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
} Glyph;

typedef struct DynamicGlyphArray
{
	Glyph* glyphs;
	unsigned int size;
} GlyphArray;

typedef struct RenderBatch
{
	GLuint offset;
	GLuint numberOfVertices;
	GLuint texture;
} RenderBatch;

typedef struct DynamicRenderBatchArray
{
	RenderBatch* batches;
	unsigned int size;
} RenderBatchArray;

typedef struct SpriteBatch
{
	GLuint vbo;
	GLuint vao;
	GlyphArray glyphs;
	GlyphSortType sortType;
	RenderBatchArray batches;
} SpriteBatch;

void dynamicInitGlyph(GlyphArray* arr, Glyph* firstGlyph);
void dynamicAddGlyph(GlyphArray* arr, Glyph* glyph);
void dynamicRemoveGlyph(GlyphArray* arr, unsigned int index);

void dynamicInitRenderBatch(RenderBatchArray* arr, RenderBatch* firstBatch);
void dynamicAddRenderBatch(RenderBatchArray* arr, RenderBatch* batch);
void dynamicRemoveRenderBatch(RenderBatchArray* arr, unsigned int index);

void initSpriteBatch(SpriteBatch* batch);
void beginSpriteBatch(SpriteBatch* batch, GlyphSortType sortType);
void endSpriteBatch(SpriteBatch* batch);
void drawSpriteBatch(SpriteBatch* batch, const vec4 rectangle, const vec4 uvRectangle, GLuint texture, float depth, const Color* color);
void renderSpriteBatch(SpriteBatch* batch);

#endif