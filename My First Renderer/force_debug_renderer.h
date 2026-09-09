#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm.hpp>

#pragma once

#ifndef FORCE_DEBUG_RENDERER_H
#define FORCE_DEBUG_RENDERER_H

#pragma once
class ForceDebugRenderer {
public:
	ForceDebugRenderer();

	unsigned int VAO;
	unsigned int VBO;
};

#endif


