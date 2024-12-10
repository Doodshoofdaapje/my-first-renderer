#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "object.h"
#include "camera.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "MyFirstRenderer";

GLFWwindow* createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void setupObjects();
void renderLoop(GLFWwindow* window, Shader& shader);
void processInput(GLFWwindow* window);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
std::vector<Object> objects;
Camera camera;

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
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Setup shaders
    Shader myShader("shader.vert", "shader.frag");

    // Setup Camera
    camera = Camera(Transform{ glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) }, glm::vec3(0.0f, 0.0f, 0.0f));

    // Setup objects
    Object origin("triangle1.obj", false, Transform{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) });
    Object object0("triangle1.obj", true, Transform{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-55.0f, 45.0f, 0.0f), glm::vec3(1.0f)});
    Object object1("triangle1.obj", true, Transform{ glm::vec3(2.0f, 2.4f, -6.0f), glm::vec3(-15.0f, 75.0f, 0.0f), glm::vec3(1.0f) });
    Object object2("triangle1.obj", true, Transform{ glm::vec3(5.0f, 1.9f, -3.0f), glm::vec3(-55.0f, 25.0f, 0.0f), glm::vec3(1.0f) });
    Object object3("triangle1.obj", true, Transform{ glm::vec3(-1.3f, 4.4f, -2.0f), glm::vec3(-35.0f, 6.0f, 0.0f), glm::vec3(1.0f) });
    Object object4("triangle1.obj", true, Transform{ glm::vec3(-2.2f, 1.2f, -1.0f), glm::vec3(-25.0f, 15.0f, 0.0f), glm::vec3(1.0f) });
    objects.push_back(origin);
    objects.push_back(object0);
    objects.push_back(object1);
    objects.push_back(object2);
    objects.push_back(object3);
    objects.push_back(object4);
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
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Background render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // Use shader
        shader.setMatrix4fv("view", camera.getViewMatrix());
        shader.setMatrix4fv("projection", camera.getProjectionMatrix());
        shader.setFloat("time", currentFrame);
        shader.use();

        // Draw objects
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i].draw(&shader);
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(1.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(-1.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(0.0f, 1.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(0.0f, -1.0f, deltaTime);
}