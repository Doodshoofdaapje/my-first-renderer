#include "transform.h"


Transform::Transform() {
	this->position = { 0,0,0 };
	this->rotation = { 0,0,0 };
	this->scale = { 1, 1, 1 };
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Transform::move(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}