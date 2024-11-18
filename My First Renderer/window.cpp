#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "object.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "MyFirstRenderer";

GLFWwindow* createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void setupObjects();
void renderLoop(GLFWwindow* window, Shader& shader);
void processInput(GLFWwindow* window);

std::vector<Object> objects;

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
    
    // Setup shaders
    Shader myShader("shader.vert", "shader.frag");

    // Setup objects
    Object object("triangle1.obj");
    objects.push_back(object);
    setupObjects();

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

void setupObjects() {
    // Generate VAOs for each object in the scene
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i].bind();
    }
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
        bool textured = true;
        float timeValue = glfwGetTime();
        shader.setFloat("time", timeValue);
        shader.setBool("textured", textured);
        shader.use();

        // Draw objects
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i].draw();
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