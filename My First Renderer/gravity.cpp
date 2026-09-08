#include "gravity.h"

Gravity::Gravity(Object* object, float gravity) {
	this->object = object;
	this->gravity = gravity;
}

void Gravity::apply() {
	RigidBody* rb = object->getComponent<RigidBody>();
	rb->force -= glm::vec3{ 0, rb->mass * gravity, 0 };
}

void Gravity::draw() {

}