#include "object.h"

Object::Object() {
    addComponent<Transform>();
}

Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    addComponent<Transform>(position, rotation, scale);
}