#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings 
// _________________________________________________________________________________________________________________________________
    
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

// _________________________________________________________________________________________________________________________________

    // Vertex Shader | Triangle1 ==============================================================
    const char *vertexShaderTriangleWithColorSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

    // Fragment Shader | Triangle1 ==============================================================
    const char *fragmentShaderTriangleWColorSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

int main()
{
    // glfw: initialize and configure
    // _________________________________________________________________________________________________________________________________
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set the major version of OpenGL to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set the minor version of OpenGL to 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set the OpenGL profile to core
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // _________________________________________________________________________________________________________________________________

    // glfw window creation
    // _________________________________________________________________________________________________________________________________
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); // Create a window object
    if (window == NULL) // Check if the window failed to create
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // Terminate GLFW
        return -1;
    }
    glfwMakeContextCurrent(window); // Make the window the current context
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the callback function for when the window is resized
    // _________________________________________________________________________________________________________________________________

    // glad: load all OpenGL function pointers
    // _________________________________________________________________________________________________________________________________
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Load all the OpenGL functions
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // _________________________________________________________________________________________________________________________________

    // Build and compile our shader program
    // _________________________________________________________________________________________________________________________________

    // Vertex Shader | Triangle1 ==============================================================
    unsigned int vertexShaderTriangleWithColor = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader object
    glShaderSource(vertexShaderTriangleWithColor, 1, &vertexShaderTriangleWithColorSource, NULL); // Attach the shader source code to the shader object
    glCompileShader(vertexShaderTriangleWithColor); // Compile the shader
    unsigned int shaderProgramTriangleWithColor = glCreateProgram(); // Create a shader program object
    glAttachShader(shaderProgramTriangleWithColor, vertexShaderTriangleWithColor); // Attach the vertex shader to the shader program

    // Fragment Shader | Triangle1 ==============================================================
    unsigned int fragmentShaderTriangleWColor = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object
    glShaderSource(fragmentShaderTriangleWColor, 1, &fragmentShaderTriangleWColorSource, NULL); // Attach the shader source code to the shader object
    glCompileShader(fragmentShaderTriangleWColor); // Compile the shader
    glAttachShader(shaderProgramTriangleWithColor, fragmentShaderTriangleWColor); // Attach the fragment shader to the shader program
    // =========================================================================================
    glLinkProgram(shaderProgramTriangleWithColor); // Link the shader program
    // Check if the shaders compiled successfully
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderTriangleWithColor, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderTriangleWithColor, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::TRIANGLE1::COMPILATION" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShaderTriangleWColor, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderTriangleWColor, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::TRIANGLE1::COMPILATION" << infoLog << std::endl;
    }
    // _________________________________________________________________________________________________________________________________

    // getting our vertex data
    // _________________________________________________________________________________________________________________________________

    // Triangle1
    // =========================================================================================
    float coloredTriangle[] = {
        -0.9f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        -0.45, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };
    // =========================================================================================
    // Rectange (with texture)
    // =========================================================================================
    float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Triangle wkth color VBO and VAO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coloredTriangle), coloredTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // the color is the last 3 floats
    glEnableVertexAttribArray(1);
    // Rectangle VBO and VAO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // The position is the first 3 floats
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // The color is the second 3 floats
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // The texture is the last 2 floats
    glEnableVertexAttribArray(2);

    // load the texture


    // _________________________________________________________________________________________________________________________________

    // render loop
while (!glfwWindowShouldClose(window))
{
    // ================================================================================================================================
    // input
    // _________________________________________________________________________________________________________________________________
    processInput(window);
    // ================================================================================================================================
    // render
    // _________________________________________________________________________________________________________________________________
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the color of the window
    glClear(GL_COLOR_BUFFER_BIT); // Clear the window
    glUseProgram(shaderProgramTriangleWithColor); // Use the shader program
    glBindVertexArray(VAOs[0]); // Bind the vertex array object
    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
    // ================================================================================================================================
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // _________________________________________________________________________________________________________________________________
    glfwSwapBuffers(window); // Swap the buffers
    glfwPollEvents(); // Poll for events
    // ================================================================================================================================
}

    glfwTerminate(); // Terminate GLFW
    return 0;
}


// _________________________________________________________________________________________________________________________________
// HELPER FUNCTIONS
// ====================================================================================================================================

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// _________________________________________________________________________________________________________________________________
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// _________________________________________________________________________________________________________________________________
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}