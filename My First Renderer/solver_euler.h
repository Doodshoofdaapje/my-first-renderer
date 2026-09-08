#ifndef SOLVER_EULER_H
#define SOLVER_EULER_H

#include "solver.h"

#pragma once
class SolverEuler : public Solver {
public:
    SolverEuler(std::vector<Object*>& objects, std::vector<std::unique_ptr<Force>>& forces)
        : Solver(objects, forces) {
    }
    void simulationStep(float dt);

private:
    void eulerStep(Object* object, float dt);
};

#endif