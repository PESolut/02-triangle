#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex shader source code
// The vertex shader is a program on the GPU that processes each vertex of a primitive (such as a line, point, or triangle) as it is passed to the GPU
// in our instance, we are passing a triangle to the GPU, so the vertex shader will process each vertex of the triangle
// its input is a single vertex with a size of 3, and its output is a single vertex with a size of 4
// we cast the input vertex to a vec4, and then set the w component to 1.0f
// our fourth value is not a reprensation of space, but for something called perspective division.

// in reality, the vertex shader is a function that takes as input a single vertex and outputs a single vertex
// the input vertex data is not in normalized device coordinates, but in local space coordinates.
// those local space coordinates are trasformed into cordinates in the visible region

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
     "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // hard coded color
    "}\0";

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

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

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode

    // create a vertex shader
     unsigned int vertexShader;
     vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a shader object, returns an unsigned int representing the shader object. 
        // The function takes in the type of shader we want to create, which in our case is a vertex shader
     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach the shader source code to the shader object
        // first argument is the shader object we want to compile, second argument is string count, third argument is the sorce code.
        // the fourth argument is the length of the source code, but we can set it to NULL and let OpenGL figure it out on its own
     glCompileShader(vertexShader); 

     // checking for compilation errors for vertex shader
     
     int  success;
     char infoLog[512];
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

     if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a shader object, returns an unsigned int representing the shader object. 
        // The function takes in the type of shader we want to create, which in our case is a fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach the shader source code to the shader object
    glCompileShader(fragmentShader);

    // checking for compilation errors for fragment shader
    int success2;
    char infoLog2[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
    if(!success2){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // shader program
    // a shader program is a collection of shaders that are linked together
    // we activate this shader program when we want to render an object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); // Create a shader program object
    // glCreateProgram returns an unsigned int representing the shader program object

    // Attach the vertex and fragment shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // Link the shaders together to the shader program we created earlier

    // checking for linking errors
    int success3;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);
    if(!success3){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Set the callback function for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Preparing for render loop 

    // Create vertices for triangle
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f,  -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
     };
     unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
     };

     unsigned int VBO, VAO, EBO; // Vertex Buffer Object and Vertex Array Object

     // init code
     glGenVertexArrays(1, &VAO); // Generate 1 vertex array object and store it in VAO
     glGenBuffers(1, &VBO);  // Generate 1 buffer object and store it in VBO
     glGenBuffers(1, &EBO);  // Generate 1 buffer object and store it in EBO
     // 1. bind the vertex array object
     glBindVertexArray(VAO); // Bind the vertex array object to the GL_ARRAY_BUFFER target
     // 2. copy our vertices array in a buffer for OpenGL to use
     glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Bind the buffer object to the GL_ARRAY_BUFFER target
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy the vertices data into the buffer's memory
     // 3. copy our index array in a element buffer for OpenGL to use
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Copy the indices data into the buffer's memory
    // 4. then set the vertex attributes pointers
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
    //  glBindBuffer(GL_ARRAY_BUFFER, 0);
     // first argument is the type of buffer we want to copy data into; which in our instance is the vbo currently bound to the GL_ARRAY_BUFFER target
     // second argument is the size of the data in bytes
     // third argument is the actual data we want to send
     // fourh argument is how we want the graphics card to manage the given data
     // for our case, we want the graphics card to manage the data as a static draw, which means the data will most likely not change at all or very rarely

     // At this point, we stored the vertex data within memory on the GPU as a vertex buffer object named VBO
     // now to actually draw the triangle, we need to tell OpenGL how to process the vertex data we have
     // we do this by creating a vertex shader, then finally; a fragment shader.

     

    // now we use the shader program with the function glUseProgram
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // now we need to tell OpenGL how to interpret the vertex data (per vertex attribute)
    // our vertex data is currently stored in the VBO, but OpenGL doesn't know the type of data or how many there are
    // we need to tell OpenGL how to interpret the vertex data so it knows how to render it
    // .. our vertex buffer data is a float array of size 9 (3 vertices, 3 floats each)
    // .. each positiion on the array is  stored as a 32 bit (4 byte) floating point value
    // .. there is no space  between each set of 3 values
    // .. the first value is at the beginning of the buffer



    // the first argument is the index of the vertex attribute we want to configure 
    // remember that we set the location of the position vertex attribute in the vertex shader with layout (location = 0)
    // the second argument is the size of the vertex attribute. the vertex attribute is a vec3 so it is composed of 3 values
    // the third argument is the type of data which is a GL_FLOAT
    // the fourth argument is whether or not we want the data to be normalized. we don't so we set it to GL_FALSE
    // the fifth argument is the stride. it is the space between consecutive vertex attributes. since the next set of position data is located exactly 3 times the size of a float away, we specify that value as the stride
    // the sixth argument is the offset of where the position data begins in the buffer. since the position data is at the start of the data array, we set the offset to 0

    // vertex array object
    // a vertex array object (VAO) can be bound just like a vertex buffer object (VBO) and any subsequent vertex attribute calls from that point on will be stored inside the VAO
    // this has the advantage that when configuring vertex attribute pointers, you only have to make those calls once and whenever we want to draw the object, we can just bind the corresponding VAO
    // this makes switching between different vertex data and attribute configurations as easy as binding a different VAO
    // a VAO stores the following:
    // .. calls to glEnableVertexAttribArray or glDisableVertexAttribArray
    // .. vertex attribute configurations via glVertexAttribPointer
    // .. vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer



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

        // Draw our first triangle
        glUseProgram(shaderProgram); // use the shader program we created earlier
        glBindVertexArray(VAO); // bind the VAO we created earlier
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the triangle
        // first argument is the mode we want to draw in
        // second argument is the number of vertices we have
        // third argument is the type of the indices


        // Swap buffers and poll events
        glfwPollEvents();
        glfwSwapBuffers(window);
        }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
