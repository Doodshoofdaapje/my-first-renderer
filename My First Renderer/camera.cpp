#include "camera.h"

Camera::Camera() {
	transform = Transform{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) };
	
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraRight = glm::normalize(glm::cross(up, camDirection));
	cameraUp = glm::cross(camDirection, cameraRight);
}

Camera::Camera(const Transform& trans, const glm::vec3& target) {
	transform = trans;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camDirection = glm::normalize(target - transform.position);
	cameraRight = glm::normalize(glm::cross(up, camDirection));
	cameraUp = glm::cross(camDirection, cameraRight);
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 view = glm::lookAt(transform.position, transform.position + camDirection, cameraUp);
	return view;
}

glm::mat4 Camera::getProjectionMatrix() {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	return projection;
}

void Camera::move(float forwardDisplacement, float sidewaysDisplacement, float deltaTime) {
	float cameraSpeed = 10 * deltaTime;

	transform.position += forwardDisplacement * camDirection * cameraSpeed;
	transform.position -= sidewaysDisplacement * cameraRight * cameraSpeed;
}

void Camera::rotate(float forwardRotation, float sidewaysRotation, float deltaTime) {
	float rotationSpeed = 100 * deltaTime;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;

	transform.rotation.x += forwardRotation * rotationSpeed;
	transform.rotation.y += sidewaysRotation * rotationSpeed;

	// Recalculate camera properties
	direction.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	direction.y = sin(glm::radians(transform.rotation.x));
	direction.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	camDirection = glm::normalize(direction);
	cameraRight = glm::normalize(glm::cross(up, camDirection));
	cameraUp = glm::cross(camDirection, cameraRight);
}
