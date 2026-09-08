#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>

#include "object.h"

#pragma once
class RigidBody : public Component {
public:
    RigidBody();
    RigidBody(float mass, bool useGravity, bool isPinned);

    float mass;
    bool useGravity;
    bool isPinned;

    void addForce(glm::vec3 force);
    void clearForce();

    glm::vec3 force;
    glm::vec3 velocity;
    glm::vec3 acceleration;
};

#endif