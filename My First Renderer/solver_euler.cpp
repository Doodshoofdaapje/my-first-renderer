#include "solver_euler.h"

void SolverEuler::simulationStep(float dt) {
	for (auto object : objects) {
		eulerStep(object, dt);
	}
}

void SolverEuler::eulerStep(Object* object, float dt) {
	RigidBody* rb = object->getComponent<RigidBody>();
	if (rb->isPinned) {
		return;
	}

	Transform* tr = object->getComponent<Transform>();
	tr->translate(rb->velocity * dt);
	rb->velocity += dt * DAMP * rb->force / rb->mass;
}