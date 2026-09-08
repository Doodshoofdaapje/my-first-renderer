#include "rigid_body.h"


RigidBody::RigidBody() {
    this->mass = 1.0;
    this->useGravity = true;
    this->isPinned = false;

    this->force = glm::vec3(0.0f, 0.0f, 0.0f);
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}
 
RigidBody::RigidBody(float mass, bool useGravity, bool isPinned) {
    this->mass = mass;
    this->useGravity = useGravity;
    this->isPinned = isPinned;

    this->force = glm::vec3(0.0f, 0.0f, 0.0f);
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::addForce(glm::vec3 force) {
    this->force += force;
}

void RigidBody::clearForce() {
    this->force = glm::vec3(0.0f, 0.0f, 0.0f);
}