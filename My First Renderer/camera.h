#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#include "Transform.h"

class Camera {
	public:
		Camera(const Transform& trans, const glm::vec3& target);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

	private:
		Transform transform;
		glm::vec3 camDirection;
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;

};

#endif