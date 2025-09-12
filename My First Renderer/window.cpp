#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "mesh_renderer.h"
#include "camera.h"
#include "light_source.h"

// Window variables
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;
const char* WINDOW_TITLE = "MyFirstRenderer";

// Function definitions, TODO: Cleanup into header file
GLFWwindow* createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void setupMeshObjects();
void renderLoop(GLFWwindow* window, Shader& shader);
void processInput(GLFWwindow* window);
void setupLights(Shader& shader, std::vector<Object*> lights);

template<typename T>
std::vector<Object*> objectsWith();

// Scene variables
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// Scene objects
std::vector<Object*> objects;
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
    camera = Camera(glm::vec3(0.0f, 8.0f, 15.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f, 8.0f, 0.0f));

    // Setup objects
    Object origin(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
    origin.addComponent<MeshRenderer>("triangle1.obj", "doghuhwhat.jpeg", false);

    Object dog(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.3f));
    dog.addComponent<MeshRenderer>("dog.obj", "", false);

    Object light1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    light1.addComponent<MeshRenderer>("triangle1.obj", "doghuhwhat.jpeg", false);
    light1.addComponent<LightSource>(glm::vec3(1.0f), glm::vec4(0.1f, 0.5f, 0.1f, 1.0f), glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, 0.35f, 0.44f);

    Object light2(glm::vec3(-15.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    light2.addComponent<MeshRenderer>("triangle1.obj", "doghuhwhat.jpeg", false);
    light2.addComponent<LightSource>(glm::vec3(1.0f), glm::vec4(0.1f, 0.5f, 0.1f, 1.0f), glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, 0.35f, 0.44f);

    objects.push_back(&origin);
    objects.push_back(&dog);
    objects.push_back(&light1);
    objects.push_back(&light2);

    setupMeshObjects();

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

template<typename T>
std::vector<Object*> objectsWith() {
    std::vector<Object*> result;
    for (auto object : objects) {
        if (object->hasComponent<T>()) {
            result.push_back(object);
        }
    }
    return result;
}

void renderLoop(GLFWwindow* window, Shader& shader) {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //std::cout << "Frames Per Second (FPS) " << 1 / deltaTime << std::endl;

        // Input
        processInput(window);

        // Background render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // Use main shader
        shader.setMatrix4fv("view", camera.getViewMatrix());
        shader.setMatrix4fv("projection", camera.getProjectionMatrix());
        shader.setFloat("time", currentFrame);
        shader.setVec3("viewPos", (*camera.getComponent<Transform>()).position);
        setupLights(shader, objectsWith<LightSource>());
        shader.use();

        // Draw objects
        for (auto object : objectsWith<MeshRenderer>()) {
            MeshRenderer* renderer = object->getComponent<MeshRenderer>();
            renderer->draw(&shader, (object->getComponent<Transform>()));
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

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(1.0f, 0.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(-1.0f, 0.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(0.0f, -1.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(0.0f, 1.0f, 0.0f, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(0.0f, 0.0f, 1.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.move(0.0f, 0.0f, -1.0f, deltaTime);

    // Rotation
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.rotate(1.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.rotate(-1.0f, 0.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.rotate(0.0f, -1.0f, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.rotate(0.0f, 1.0f, deltaTime);
}

void setupMeshObjects() {
    // Generate VAOs for each object in the scene
    for (auto object : objectsWith<MeshRenderer>()) {
        MeshRenderer* renderer = object->getComponent<MeshRenderer>();
        renderer->bind();
    }
}

void setupLights(Shader& shader, std::vector<Object*> lights) {
    int numLights = lights.size();
    shader.setInt("numLights", numLights);

    for (int i = 0; i < numLights; ++i) {
        std::string index = "lights[" + std::to_string(i) + "]";

        Object* light = lights[i];
        LightSource* lightComponent = lights[i]->getComponent<LightSource>();

        shader.setVec3(index + ".position", light->getComponent<Transform>()->position);

        shader.setVec3(index + ".color", lightComponent->getColor());
        shader.setVec4(index + ".ambient", lightComponent->getAmbient());
        shader.setVec4(index + ".diffuse", lightComponent->getDiffuse());
        shader.setVec4(index + ".specular", lightComponent->getSpecular());

        shader.setFloat(index + ".kConstant", lightComponent->getKConstant());
        shader.setFloat(index + ".kLinear", lightComponent->getKLinear());
        shader.setFloat(index + ".KQuadratic", lightComponent->getKQuadratic());
    }
}