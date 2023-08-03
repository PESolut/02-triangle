#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings 
// _________________________________________________________________________________________________________________________________
    
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

// _________________________________________________________________________________________________________________________________

int main()
{
    // _________________________________________________________________________________________________________________________________
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
    // render loop
    // _________________________________________________________________________________________________________________________________
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