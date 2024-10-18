#include "spritebatch.h"
#include <stdlib.h>
#include "errors.h"
#include "dynamicvecs.h"

void dynamicInitGlyph(GlyphArray* arr, Glyph* firstGlyph)
{
	arr->glyphs = (Glyph*)malloc(sizeof(Glyph));
	if (arr->glyphs == NULL)
	{
		fatalError("Failed to initialize GlyphArray.");
		return;
	}
	arr->glyphs = firstGlyph;
	arr->size = 1;
}

void dynamicAddGlyph(GlyphArray* arr, Glyph* glyph)
{
	arr->size++;
	Glyph* a = (Glyph*)malloc(arr->size * sizeof(Glyph));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: GlyphArray Add");
		return;
	}
	for (int i = 0; i < arr->size - 1; i++) a[i] = arr->glyphs[i];
	a[arr->size - 1] = *glyph;
	arr->glyphs = a;
}

void dynamicRemoveGlyph(GlyphArray* arr, unsigned int index)
{
	if (index >= arr->size) return;
	Glyph* a = (Glyph*)malloc((arr->size - 1) * sizeof(Glyph));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: GlyphArray Remove");
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
		a[i - off] = arr->glyphs[i];
	}
	arr->size--;
	arr->glyphs = a;
}

void dynamicInitRenderBatch(RenderBatchArray* arr, RenderBatch* firstBatch)
{
	arr->batches = (RenderBatch*)malloc(sizeof(RenderBatch));
	if (arr->batches == NULL)
	{
		fatalError("Failed to initialize RenderBatchArray.");
		return;
	}
	arr->batches = firstBatch;
	arr->size = 1;
}

void dynamicAddRenderBatch(RenderBatchArray* arr, RenderBatch* batch)
{
	arr->size++;
	RenderBatch* a = (RenderBatch*)malloc(arr->size * sizeof(RenderBatch));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: RenderBatchArray Add");
		return;
	}
	for (int i = 0; i < arr->size - 1; i++) a[i] = arr->batches[i];
	a[arr->size - 1] = *batch;
	arr->batches = a;
}

void dynamicRemoveRenderBatch(RenderBatchArray* arr, unsigned int index)
{
	if (index >= arr->size) return;
	RenderBatch* a = (RenderBatch*)malloc((arr->size - 1) * sizeof(RenderBatch));
	if (a == NULL)
	{
		fatalError("Failed to allocate memory: RenderBatchArray Remove");
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
		a[i - off] = arr->batches[i];
	}
	arr->size--;
	arr->batches = a;
}

void createRenderBatches(SpriteBatch* batch)
{
	if (batch->glyphs.size == 0) return;

	VertexArray vertices;
	vertices.vertices = (Vertex*)malloc(batch->glyphs.size * 6 * sizeof(Vertex));
	if (vertices.vertices == NULL) fatalError("Memory error trying to allocate memory for vertices.");
	vertices.size = batch->glyphs.size * 6;

	unsigned int offset = 0;
	RenderBatch newBatch;
	newBatch.offset = offset;
	newBatch.numberOfVertices = 6;
	newBatch.texture = batch->glyphs.glyphs[0].texture;
	dynamicInitRenderBatch(&batch->batches, &newBatch);

	unsigned int currentVertex = 0;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].topLeft;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].bottomLeft;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].bottomRight;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].bottomRight;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].topRight;
	vertices.vertices[currentVertex++] = batch->glyphs.glyphs[0].topLeft;
	offset += 6;

	for (unsigned int currentGlyph = 1; currentGlyph < batch->glyphs.size; currentGlyph++)
	{
		if (batch->glyphs.glyphs[currentGlyph].texture != batch->glyphs.glyphs[currentGlyph - 1].texture)
		{
			newBatch.offset = offset;
			newBatch.texture = batch->glyphs.glyphs[currentGlyph].texture;
			dynamicAddRenderBatch(&batch->batches, &newBatch);
		}
		else
		{
			batch->batches.batches[batch->batches.size - 1].numberOfVertices += 6;
		}

		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].topLeft;
		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].bottomLeft;
		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].bottomRight;
		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].bottomRight;
		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].topRight;
		vertices.vertices[currentVertex++] = batch->glyphs.glyphs[currentGlyph].topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size * sizeof(Vertex), vertices.vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void createVertexArray(SpriteBatch* batch)
{
	if (batch->vao == 0) glGenVertexArrays(1, &batch->vao);
	glBindVertexArray(batch->vao);

	if (batch->vbo == 0) glGenBuffers(1, &batch->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

int compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}

int compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}

int comapareByTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}

void swap(Glyph* a, Glyph* b)
{
	Glyph temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Glyph* arr, int lowIndex, int highIndex, void* booleanFunction)
{
	Glyph pivot = arr[highIndex];
	int i = lowIndex - 1;
	for (unsigned int j = lowIndex; j <= highIndex - 1; j++)
	{
		if (((int(*)(Glyph*, Glyph*))booleanFunction)(&arr[j], &pivot))
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[highIndex]);
	return i + 1;
}

void quickSort(Glyph* arr, int lowIndex, int highIndex, void* booleanFunction)
{
	if (lowIndex < highIndex)
	{
		int pivot = partition(arr, lowIndex, highIndex, booleanFunction);

		quickSort(arr, lowIndex, pivot - 1, booleanFunction);
		quickSort(arr, pivot + 1, highIndex, booleanFunction);
	}
}

void sortGlyphs(SpriteBatch* batch)
{
	switch (batch->sortType)
	{
	case FRONT_TO_BACK:
		quickSort(batch->glyphs.glyphs, 0, batch->glyphs.size - 1, compareFrontToBack);
		break;
	case BACK_TO_FRONT:
		quickSort(batch->glyphs.glyphs, 0, batch->glyphs.size - 1, compareBackToFront);
		break;
	case BY_TEXTURE:
		quickSort(batch->glyphs.glyphs, 0, batch->glyphs.size - 1, comapareByTexture);
		break;
	}
}

void initSpriteBatch(SpriteBatch* batch)
{
	batch->vao = 0;
	batch->vbo = 0;
	batch->glyphs.size = 0;
	createVertexArray(batch);
}

void beginSpriteBatch(SpriteBatch* batch, GlyphSortType sortType)
{
	batch->sortType = sortType;
	batch->glyphs.size = 0;
}

void endSpriteBatch(SpriteBatch* batch)
{
	sortGlyphs(batch);
	createRenderBatches(batch);
}

void drawSpriteBatch(SpriteBatch* batch, const vec4 rectangle, const vec4 uvRectangle, GLuint texture, float depth, const Color* color)
{
	Glyph newGlyph;
	newGlyph.texture = texture;
	newGlyph.depth = depth;

	setColor(&newGlyph.topLeft, color->r, color->g, color->b, color->a);
	setPosition(&newGlyph.topLeft, rectangle[0], rectangle[1] + rectangle[3]);
	setUV(&newGlyph.topLeft, uvRectangle[0], uvRectangle[1] + uvRectangle[3]);

	setColor(&newGlyph.bottomLeft, color->r, color->g, color->b, color->a);
	setPosition(&newGlyph.bottomLeft, rectangle[0], rectangle[1]);
	setUV(&newGlyph.bottomLeft, uvRectangle[0], uvRectangle[1]);

	setColor(&newGlyph.bottomRight, color->r, color->g, color->b, color->a);
	setPosition(&newGlyph.bottomRight, rectangle[0] + rectangle[2], rectangle[1]);
	setUV(&newGlyph.bottomRight, uvRectangle[0] + uvRectangle[2], uvRectangle[1]);

	setColor(&newGlyph.topRight, color->r, color->g, color->b, color->a);
	setPosition(&newGlyph.topRight, rectangle[0] + rectangle[2], rectangle[1] + rectangle[3]);
	setUV(&newGlyph.topRight, uvRectangle[0] + uvRectangle[2], uvRectangle[1] + uvRectangle[3]);
	
	dynamicAddGlyph(&batch->glyphs, &newGlyph);
}

void renderSpriteBatch(SpriteBatch* batch)
{
	glBindVertexArray(batch->vao);

	for (unsigned int i = 0; i < batch->batches.size; i++)
	{
		glBindTexture(GL_TEXTURE_2D, batch->batches.batches[i].texture);
		glDrawArrays(GL_TRIANGLES, batch->batches.batches[i].offset, batch->batches.batches[i].numberOfVertices);
	}

	glBindVertexArray(0);
}