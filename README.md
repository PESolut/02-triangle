# OpenGL Triangle Example
This is a simple C++ program that demonstrates how to create an OpenGL window, set up a triangle, and render it on the screen using modern OpenGL.

## Dependencies

### GLFW:
You need to have GLFW installed on your system. GLFW is a multi-platform library for creating windows with OpenGL contexts and handling input. Visit the GLFW website (https://www.glfw.org/) to download and install it.

### GLAD: 
GLAD is used to load the OpenGL function pointers. You can download the GLAD headers and source files from the GLAD website (https://glad.dav1d.de/) and include them in your project.

### Build Instructions
After installing GLFW and including GLAD in your project, you can build the program using any C++ compiler that supports C++11 or later. For example, with GCC:


#### Copy code

```bash
g++ -o main main.cpp -lglfw -ldl
```

#### Execute code
After running the command, assuming no errors; Simply run the compiled executable to see the OpenGL window displaying a colored triangle.

## Description
The software initializes an OpenGL context and creates a window using GLFW. It employs a core OpenGL profile and sets the OpenGL version to 3.3.

In normalized device coordinates (NDC), a float array is used to represent the vertex information for triangles. A vertex buffer object (VBO) is subsequently created on the GPU to store the vertex data. The vertex data is copied into the buffer's memory using glBufferData, and the VBO is tied to the GL_ARRAY_BUFFER target. Due of the fact that vertex data won't change frequently, the graphics card manages this information as a static draw.

A render loop is used to complete the rendering process. Using glClearColor and glClear, the loop uses a specific color to clean the screen. By converting RGB values (0–255) to float values between 0 and 1, the color is chosen.

The application looks for user input before closing the window when the ESC key is pushed after each loop iteration. To display the rendered frame, the window switches and updates the buffers.

at this point, the software doesn't have any shaders.