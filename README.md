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
  - Returns an initialized camera struct. This function should be used whenever a new camera is created.

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

void DMB_SetMouseToCamera(Camera2D* camera, Mouse* mouse, vec2 cameraCoords)
  - camera - a pointer to a camera struct.
  - mouse - a pointer to a mouse struct.
  - cameraCoords - a cglm vector, the new mouse coordinates with reference to the camera position. This parameter will be modified by the function.

void DMB_KeyDown(int sdl_key, int* keys, Mouse* mouse)
  - sdl_key - The SDL_Event event.key.keysym.sym.
  - keys - an array for tracking which keys get pressed.
  - mouse - a pointer to a mouse struct.
  - Updates the keys array / mouse struct by noting which key is pressed.

void DMB_KeyUp(int sdl_key, int* keys, Mouse* mouse)
  - sdl_key - The SDL_Event event.key.keysym.sym.
  - keys - an array for tracking which keys get pressed.
  - mouse - a pointer to a mouse struct.
  - Updates the keys array / mouse struct by noting which key is released.

Mouse DMB_InitMouse()
  - Returns an initialized mouse struct. This function should be used whenever a new mouse is created.

void DMB_SetMouseCoords(Mouse* mouse, float x, float y)
  - mouse - a pointer to a mouse struct.
  - x - the mouse x.
  - y - the mouse y.
  - This function should be used when handling inputs, its purpose is to update the mouse struct to reflect the position of the mouse whenver it moves.

void DMB_CompileShaders(GLSLProgram* glsl, const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
  - glsl - a pointer to a GLSLProgram struct.
  - vertexShaderFilePath - the file path to the vertex shader program file.
  - fragmentShaderFilePath - the file path to the fragment shader program file.
  - Compiles the vertex and fragment shaders and stores the necessary information in the GLSLProgram struct.

void DMB_AddAttribute(GLSLProgram* glsl, const char* attributeName)
  - glsl - a pointer to a GLSLProgram sruct.
  - attributeName - the name of the attribute in the GLSL shader program.
  - Attributes should be added after compilation and before linking. The name must match exactly to what is in the shader programs.
