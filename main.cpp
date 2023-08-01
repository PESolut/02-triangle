#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

// Function to process input
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() { 
    // Initialize GLFW
    glfwInit();
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints ( we are using version 3.3, we also are forward compatible)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the current window the main context
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
    }   

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Set the callback function for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Render loop
    while(!glfwWindowShouldClose(window)){
        // Process input every iteration of the loop
        processInput(window);

        // Render commands here

        // setting colors to be a float value between 0 and 1 (RPG value / 255)
        // see:  https://stackoverflow.com/questions/46524896/understanding-glclearcolor-values
        // also: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml
        float rValue = 51.0f / 255.0f;
        float gValue = 102.0f / 255.0f;
        float bValue = 153.0f / 255.0f;
        glClearColor(rValue, gValue, bValue, 1.0f); // Set the color of the screen by changing state of OpenGL ( state setting )
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with the color we set in glClearColor ( state using )


        // Swap buffers and poll events
        glfwPollEvents();
        glfwSwapBuffers(window);
        }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
