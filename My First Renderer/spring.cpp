#include "spring.h"
#include <glad/glad.h> // include glad to get all the required OpenGL headers

Spring::Spring(Object& obj1, Object& obj2, double dist, double ks, double kd) :
	obj1(obj1), obj2(obj2), dist(dist), ks(ks), kd(kd) {

	// Create shader objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Set VAO and VBO for use
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Set pointers to attributes
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind buffer and array
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void Spring::draw()
{
	Transform* tr1 = obj1.getComponent<Transform>();
	Transform* tr2 = obj2.getComponent<Transform>();

	glm::vec3 vertices[] = {
		tr1->position,
		tr2->position
	};

	// Select the force's data to be loaded in
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Select force's array to use for data
	glBindVertexArray(VAO);

	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}