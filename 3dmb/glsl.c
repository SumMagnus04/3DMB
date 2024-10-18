#include <stdlib.h>
#include <stdio.h>
#include "glsl.h"
#include "errors.h"

char* readShaderProgram(const char* filePath)
{
	FILE* file;
	int size = 0;
	char* buffer = NULL;

	fopen_s(&file, filePath, "r");
	if (file == NULL)
	{
		fatalError("Failed to open file.");
		return NULL;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) size++;

	buffer = (char*)malloc(size + 1);
	if (buffer == NULL)
	{
		fclose(file);
		fatalError("Memory error.");
		return NULL;
	}

	rewind(file);

	int i = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		if (i < size) buffer[i] = ch;
		i++;
	}
	buffer[size] = '\0';

	fclose(file);

	return buffer;
}

void DMB_CompileShaders(GLSLProgram* glsl, const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
	glsl->programID = glCreateProgram();

	glsl->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (glsl->vertexShaderID == 0) fatalError("Vertex shader failed to be created.");

	glsl->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (glsl->fragmentShaderID == 0) fatalError("Fragment shader failed to be created");

	const char* vertexShaderProgram = readShaderProgram(vertexShaderFilePath);
	if (vertexShaderProgram == NULL) fatalError("Failed to read vertex shader.");

	glShaderSource(glsl->vertexShaderID, 1, &vertexShaderProgram, NULL);
	glCompileShader(glsl->vertexShaderID);

	GLint success = 0;
	glGetShaderiv(glsl->vertexShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glDeleteShader(glsl->vertexShaderID);
		fatalError("Failed to compile vertex shader.");
	}

	const char* fragmentShaderProgram = readShaderProgram(fragmentShaderFilePath);
	if (fragmentShaderProgram == NULL) fatalError("Failed to read fragment shader");

	glShaderSource(glsl->fragmentShaderID, 1, &fragmentShaderProgram, NULL);
	glCompileShader(glsl->fragmentShaderID);

	success = 0;
	glGetShaderiv(glsl->fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glDeleteShader(glsl->fragmentShaderID);
		fatalError("Failed to compile fragment shader.");
	}
}

void DMB_AddAttribute(GLSLProgram* glsl, const char* attributeName)
{
	glBindAttribLocation(glsl->programID, glsl->numAttributes++, attributeName);
}

void DMB_LinkShaders(GLSLProgram* glsl)
{
	glAttachShader(glsl->programID, glsl->vertexShaderID);
	glAttachShader(glsl->programID, glsl->fragmentShaderID);

	glLinkProgram(glsl->programID);

	GLint success = 0;
	glGetProgramiv(glsl->programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glDeleteProgram(glsl->programID);
		glDeleteShader(glsl->vertexShaderID);
		glDeleteShader(glsl->fragmentShaderID);
		fatalError("Failed to link shaders.");
	}

	glDetachShader(glsl->programID, glsl->vertexShaderID);
	glDetachShader(glsl->programID, glsl->fragmentShaderID);
	glDeleteShader(glsl->vertexShaderID);
	glDeleteShader(glsl->fragmentShaderID);
}

void DMB_UseGLSLProgram(GLSLProgram* glsl)
{
	glUseProgram(glsl->programID);
	for (int i = 0; i < glsl->numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void DMB_UnuseGLSLProgram(GLSLProgram* glsl)
{
	glUseProgram(0);
	for (int i = 0; i < glsl->numAttributes; i++)
		glDisableVertexAttribArray(i);
}

GLint DMB_GetUniformLocation(GLSLProgram* glsl, const char* uniformName)
{
	GLint location = glGetUniformLocation(glsl->programID, uniformName);
	if (location == GL_INVALID_INDEX) fatalError("Uniform not found in shader.");
	return location;
}