#ifndef SOLVER_H
#define SOLVER_H

#define DAMP 0.95f

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>

#include "object.h"
#include "rigid_body.h"
#include "force.h"

#pragma once
class Solver {

protected:
    std::vector<std::unique_ptr<Force>>& forces;
    std::vector<Object*>& objects;

public:
    Solver(std::vector<Object*>& objects, std::vector<std::unique_ptr<Force>>& forces)
        : objects(objects), forces(forces) {
    }

    virtual ~Solver() = default;
    virtual void simulationStep(float dt) = 0;

};

#endif