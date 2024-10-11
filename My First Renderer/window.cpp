#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "MyFirstRenderer";

GLFWwindow* createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void setupVertexData();
void bindVertices(float vertices[], size_t size, unsigned int VAO);
void renderLoop(GLFWwindow* window, Shader& shader);
void processInput(GLFWwindow* window);

// Triangle 1
float triangle1_vertices[] = {
 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
-0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
 0.0f, -0.1f, 0.0f,   1.0f, 0.0f, 0.0f
};

// Triangle 2
float triangle2_vertices[] = {
-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
 0.0f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,
};

unsigned int VAO[3];

int main()
{
    GLFWwindow* window = createWindow();
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Resize event handlr
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Setup vertices
    setupVertexData();

    // Setup shaders
    Shader myShader("shader_vertex.txt", "shader_fragment.txt");
   
    // Start rendering
    renderLoop(window, myShader);

    // Release all resource allocations
    glfwTerminate();
    return 0;
}

GLFWwindow* createWindow() {
    // Create context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setupVertexData() {
    // Generate two VAOs and store them in the VAO array
    glGenVertexArrays(3, VAO);

    // Bind triangles
    bindVertices(triangle1_vertices, sizeof(triangle1_vertices), VAO[0]);
    bindVertices(triangle2_vertices, sizeof(triangle2_vertices), VAO[1]);
    
}

void bindVertices(float vertices[], size_t size, unsigned int VAO) {
    // Bind to array
    glBindVertexArray(VAO);

    // Object data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Specify color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind buffer and array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void renderLoop(GLFWwindow* window, Shader& shader) {
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Background render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use shader
        shader.use();

        // Draw objects
        for (int i = 0; i < sizeof(VAO) / sizeof(VAO[0]); i++) {
            glBindVertexArray(VAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        
        // Check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}