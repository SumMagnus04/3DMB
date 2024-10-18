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
  - Initializes the DMB_WINDOW.
