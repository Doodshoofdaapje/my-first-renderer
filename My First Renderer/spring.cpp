#include "spring.h"

Spring::Spring(Object& obj1, Object& obj2, double dist, double ks, double kd) :
	obj1(obj1), obj2(obj2), dist(dist), ks(ks), kd(kd) {
}

void Spring::apply() {
	Transform* tr1 = obj1.getComponent<Transform>();
	Transform* tr2 = obj2.getComponent<Transform>();
	RigidBody* rb1 = obj1.getComponent<RigidBody>();
	RigidBody* rb2 = obj2.getComponent<RigidBody>();


	glm::vec3 length = tr1->position - tr2->position;
	glm::vec3 lengthDer = rb1->velocity - rb2->velocity;
	float lengthNorm = glm::sqrt(glm::dot(lengthDer, lengthDer));

	if (lengthNorm == 0) {
		return;
	}

	float springComponent = ks * (lengthNorm - dist);
	float dampingComponent = kd * glm::dot(length, lengthDer) / lengthNorm;
	float scalar = -(springComponent + dampingComponent) / lengthNorm;
	glm::vec3 force = length * scalar;

	rb1->force += force;
	rb2->force -= force;
}


std::vector<glm::vec3> Spring::getDebugVector() {
	Transform* tr1 = obj1.getComponent<Transform>();
	Transform* tr2 = obj2.getComponent<Transform>();

	std::vector<glm::vec3> debugVector = { tr1->position, tr2->position };

	return debugVector;
}