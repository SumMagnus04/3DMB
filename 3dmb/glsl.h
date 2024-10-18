#ifndef GLSL_H
#define GLSL_H

#include <GL/glew.h>

typedef struct GLSLProgram
{
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	int numAttributes;
} GLSLProgram;

void DMB_CompileShaders(GLSLProgram* glsl, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
void DMB_AddAttribute(GLSLProgram* glsl, const char* attributeName);
void DMB_LinkShaders(GLSLProgram* glsl);
void DMB_UseGLSLProgram(GLSLProgram* glsl);
void DMB_UnuseGLSLProgram(GLSLProgram* glsl);
GLint DMB_GetUniformLocation(GLSLProgram* glsl, const char* uniformName);

#endif