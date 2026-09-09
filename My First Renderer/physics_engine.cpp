#include "physics_engine.h"
#include "rigid_body.h"
#include "solver_runge_kutta_4.h"
#include "solver_euler.h"
#include "gravity.h"
#include "spring.h"

PhysicsEngine::PhysicsEngine() {
	this->solver = std::make_unique<SolverEuler>(objects, forces);
	this->enabled = false;
}

void PhysicsEngine::registerObject(Object* object) {
	if (!object->hasComponent<RigidBody>()) {
		return;
	}

	RigidBody* rb = object->getComponent<RigidBody>();
	if (rb->useGravity) {
		forces.push_back(std::make_unique<Gravity>(object, 9.81f));
	}

	objects.push_back(object);
}

void PhysicsEngine::registerForce(std::unique_ptr<Force> force) {
	forces.push_back(std::move(force));
}

std::vector<Force*> PhysicsEngine::getForces() {
	std::vector<Force*> results;
	for (auto& force : forces) {
		results.push_back(force.get());
	}
	return results;
}

void PhysicsEngine::clearForces() {
	for (Object* object : objects) {
		RigidBody* rb = object->getComponent<RigidBody>();
		rb->clearForce();
	}
}

void PhysicsEngine::applyForces() {
	for (auto& force : forces) {
		force->apply();
	}
}

void PhysicsEngine::simulationStep(float dt) {
	if (!enabled) {
		return;
	}
	clearForces();
	applyForces();
	solver->simulationStep(dt);
}

void PhysicsEngine::toggleSimulation() {
	this->enabled = !this->enabled;
}