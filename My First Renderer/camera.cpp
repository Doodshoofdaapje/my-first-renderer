#include "camera.h"

Camera::Camera(const Transform& trans, const glm::vec3& target) {
	transform = trans;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camDirection = trans.position - target;
	cameraRight = glm::normalize(glm::cross(up, camDirection));
	cameraUp = glm::cross(camDirection, cameraRight);
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 view = glm::lookAt(transform.position, camDirection, cameraUp);
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));
	return view;
}

glm::mat4 Camera::getProjectionMatrix() {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	return projection;
}
