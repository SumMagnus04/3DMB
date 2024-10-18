#include "win.h"
#include "errors.h"
#include <stdio.h>
#include <GL/glew.h>

int DMB_CreateWindow(const char* name, int screenWidth, int screenHeight, unsigned int currentFlags)
{
	DMB_SCREEN_WIDTH = screenWidth;
	DMB_SCREEN_HEIGHT = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE) flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;

	DMB_WINDOW = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (DMB_WINDOW == NULL) fatalError("SDL Window could not be created.");

	SDL_GLContext glContext = SDL_GL_CreateContext(DMB_WINDOW);
	if (glContext == NULL) fatalError("SDL_GL context could not be created.");

	GLenum error = glewInit();
	if (error != GLEW_OK) fatalError("Could not initialize glew.");

	printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	glClearColor(1.0f, 0.33f, 0.25f, 1.0f);

	SDL_GL_SetSwapInterval(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}