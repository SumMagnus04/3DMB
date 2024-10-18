Additional required libraries:
  - SDL2
  - glew
  - cglm

Library functions:

void DMB_Init()
  - Required before using any other DMB functions.
  - Initializes SDL.

void DMB_CreateWindow(const char* name, int screenWidth, int screenHeight, unsigned int currentFlags)
  - name - the name of the window.
  - screenWidth - the width of the window.
  - screenHeight - the height of the window.
  - currentFlags - NONE, INVISIBLE, FULLSCREEN, BORDERLESS
  - Initializes the DMB_WINDOW.

Camera DMB_InitCamera(int screenWidth, int screenHeight)
  - screenWidth - the screen width.
  - screenHeight - the screen height.
  - Returns an initialized camera struct.

void DMB_SetPositionCamera2D(Camera2D* camera, vec2 newPosition)
  - camera - a pointer to a camera struct.
  - newPosition - a cglm vector, the new position of the camera.

void DMB_SetScaleCamera2D(Camera2D* camera, float newScale)
  - camera - a pointer to a camera struct.
  - newScale - the new scale of the camera.

void DMB_UpdateCamera2D(Camera2D* camera)
  - camera - a pointer to a camera struct.
  - Updates the camera matrix if the position or scale of the camera has been changes recently.
  - Should be called in the game loop.

Mouse DMB_InitMouse()
  - Returns an initialized mouse struct.


