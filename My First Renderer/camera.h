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

#include "object.h"
#include "transform.h"

class Camera : public Object {
	public:
		Camera();
		Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const glm::vec3& target);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		void move(float forwardDisplacement, float sidewaysDisplacement, float verticalDisplacement, float deltaTime);
		void rotate(float forwardRotation, float sidewaysRotation, float deltaTime);

	private:
		glm::vec3 camDirection;
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;

};

#endif