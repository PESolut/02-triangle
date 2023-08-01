#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>


int main() { 
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    return 0;
}
