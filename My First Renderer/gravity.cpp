#include "gravity.h"

Gravity::Gravity(Object* object, float gravity) {
	this->object = object;
	this->gravity = gravity;
}

void Gravity::apply() {
	RigidBody* rb = object->getComponent<RigidBody>();
	rb->force -= glm::vec3{ 0, rb->mass * gravity, 0 };
}

std::vector<glm::vec3> Gravity::getDebugVector() {
	Transform* tr1 = object->getComponent<Transform>();
	return { tr1->position, tr1->position - glm::vec3{0, gravity / 5, 0} };
}