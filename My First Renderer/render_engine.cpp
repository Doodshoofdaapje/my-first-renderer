#include "render_engine.h"
#include "mesh_renderer.h"

RenderEngine::RenderEngine() : shader("shader.vert", "shader.frag")  {
}

void RenderEngine::setMeshObjects(const std::vector<Object*> meshObjects) {
    this->meshObjects = meshObjects;

    // Generate VAOs for each mesh object
    for (auto object : meshObjects) {
        MeshRenderer* renderer = object->getComponent<MeshRenderer>();
        renderer->setup();
    }
}
void RenderEngine::setLights(const std::vector<Object*> lights) {
    this->lights = lights;
}
void RenderEngine::setForces(const std::vector<Force*> forces) {
    this->forces = forces;
}

void RenderEngine::updateLights() {
    int numLights = lights.size();
    shader.setInt("numLights", numLights);

    for (int i = 0; i < numLights; ++i) {
        std::string index = "lights[" + std::to_string(i) + "]";

        Object* light = lights[i];
        LightSource* lightComponent = light->getComponent<LightSource>();

        shader.setVec3(index + ".position", light->getComponent<Transform>()->position);

        shader.setVec4(index + ".ambient", lightComponent->getAmbient());
        shader.setVec4(index + ".diffuse", lightComponent->getDiffuse());
        shader.setVec4(index + ".specular", lightComponent->getSpecular());

        shader.setFloat(index + ".kConstant", lightComponent->getKConstant());
        shader.setFloat(index + ".kLinear", lightComponent->getKLinear());
        shader.setFloat(index + ".KQuadratic", lightComponent->getKQuadratic());
    }
}

void RenderEngine::drawMeshObjects() {
    for (auto object : meshObjects) {
        MeshRenderer* renderer = object->getComponent<MeshRenderer>();
        renderer->draw(&shader, (object->getComponent<Transform>()));
    }
}

void RenderEngine::drawForces() {
    for (auto force : forces) {
        force->draw();
    }
}

void RenderEngine::render(Camera& camera) {
    // Background render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Setup shader values for objects
    shader.setMatrix4fv("view", camera.getViewMatrix());
    shader.setMatrix4fv("projection", camera.getProjectionMatrix());
    shader.setVec3("viewPos", (*camera.getComponent<Transform>()).position);
    updateLights();
    shader.use();

    drawMeshObjects();

    // Draw forces
    shader.setMatrix4fv("model", glm::mat4(1.0f));
    
    drawForces();
}