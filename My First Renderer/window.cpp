#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "mesh_renderer.h"
#include "camera.h"
#include "light_source.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "spring.h"

// Window variables
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;
const char* WINDOW_TITLE = "MyFirstRenderer";

// Function definitions, TODO: Cleanup into header file
GLFWwindow* createWindow();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

void simulationLoop(GLFWwindow* window);
void processInput(GLFWwindow* window);

// TODO: move to scene object
template<typename T>
std::vector<Object*> objectsWith();

// Scene variables
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float mouseX = 400.0f;
float mouseY = 300.0f;
bool firstMouse = true;

// Scene objects
std::vector<std::unique_ptr<Object>> objects;
std::unique_ptr<RenderEngine> renderEngine;
PhysicsEngine physicsEngine;
Camera camera;

int main()
{
    GLFWwindow* window = createWindow();
    glfwMakeContextCurrent(window); 
    glfwSetWindowPos(window, 700, 100);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Resize event handlr
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Initialize renderer after window context exists
    renderEngine = std::make_unique<RenderEngine>();

    // Callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide and lock cursor
    
    // Setup Camera
    camera = Camera(glm::vec3(0.0f, 8.0f, 15.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f, 8.0f, 0.0f));

    // Setup objects
    std::unique_ptr<Object> origin = std::make_unique<Object>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f));
    origin->addComponent<MeshRenderer>("triangle1.obj")->setTexture(true, "doghuhwhat.jpeg");

    std::unique_ptr<Object> ground = std::make_unique<Object>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
    ground->addComponent<MeshRenderer>("ground.obj");

    std::unique_ptr<Object> dog = std::make_unique<Object>(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.3f));
    dog->addComponent<MeshRenderer>("dog.obj")->setMaterial(128, glm::vec4(0.2, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f));

    std::unique_ptr<Object> light1 = std::make_unique<Object>(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
    light1->addComponent<MeshRenderer>("triangle1.obj");
    light1->addComponent<LightSource>(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), 1.0f, 0.09f, 0.032f);
    light1->addComponent<RigidBody>(1.0f, true, true);

    std::unique_ptr<Object> light2 = std::make_unique<Object>(glm::vec3(-15.0f, 30.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    light2->addComponent<MeshRenderer>("triangle1.obj");
    light2->addComponent<LightSource>(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(1.0f), glm::vec4(1.0f), 1.0f, 0.35f, 0.44f);
    light2->addComponent<RigidBody>(1.0f, true, false);

    physicsEngine.registerForce(std::make_unique<Spring>(*light1, *light2, 0.1, 0.15, 0.015));

    objects.push_back(std::move(origin));
    objects.push_back(std::move(ground));
    objects.push_back(std::move(dog));
    objects.push_back(std::move(light1));
    objects.push_back(std::move(light2));

    renderEngine->setMeshObjects(objectsWith<MeshRenderer>());
    renderEngine->setLights(objectsWith<LightSource>());
    renderEngine->setForces(physicsEngine.getForces());

    for (auto object : objectsWith<RigidBody>()) {
        physicsEngine.registerObject(object);
    }

    // Start rendering
    simulationLoop(window);

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

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        mouseX = (float)xpos;
        mouseY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - mouseX;
    float yoffset = mouseY - (float)ypos;

    mouseX = (float)xpos;
    mouseY = (float)ypos;

    camera.rotate(yoffset, xoffset);
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

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        physicsEngine.toggleSimulation();
}

template<typename T>
std::vector<Object*> objectsWith() {
    std::vector<Object*> result;
    for (auto& object : objects) {
        if (object->hasComponent<T>()) {
            result.push_back(object.get());
        }
    }
    return result;
}

void simulationLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //std::cout << "Frames Per Second (FPS) " << 1 / deltaTime << std::endl;

        // Input
        processInput(window);

        // Physics
        physicsEngine.simulationStep(deltaTime);

        // Rendering
        renderEngine->render(camera);
        
        // Check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}