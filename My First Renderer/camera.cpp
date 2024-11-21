#include "camera.h"

Camera::Camera(const Transform& trans, const glm::vec3& target) {
	transform = trans;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camDirection = glm::normalize(trans.position - target);
	cameraRight = glm::normalize(glm::cross(up, camDirection));
	cameraUp = glm::cross(camDirection, cameraRight);
}

glm::mat4 Camera::getViewMatrix() {
	// Temp
	const float radius = 10.0f;
	transform.position.x = sin(glfwGetTime()) * radius;
	transform.position.z = cos(glfwGetTime()) * radius;

	glm::mat4 view = glm::lookAt(transform.position, camDirection, cameraUp);
	return view;
}

glm::mat4 Camera::getProjectionMatrix() {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	return projection;
}
