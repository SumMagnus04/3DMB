Additional required libraries:
  - SDL2
  - glew
  - cglm

Library functions:

void DMB_Init()
  - Required before using any other DMB functions.
  - Initializes SDL.

DMB_CreateWindow(const char* name, int screenWidth, int screenHeight, unsigned int currentFlags)
  - name - the name of the window.
  - screenWidth - the width of the window.
  - screenHeight - the height of the window.
  - currentFlags - NONE, INVISIBLE, FULLSCREEN, BORDERLESS
  - Initializes the DMB_WINDOW.
