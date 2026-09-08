#ifndef SOLVER_RUNGE_KUTTA_H
#define SOLVER_RUNGE_KUTTA_H

#include "solver.h"

#pragma once
class SolverRungeKutta4 : public Solver {
public:
    SolverRungeKutta4(std::vector<Object*>& objects, std::vector<std::unique_ptr<Force>>& forces)
        : Solver(objects, forces) {
    }
    void simulationStep(float dt);

};

#endif