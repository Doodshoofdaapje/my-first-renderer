#include "force_debug_renderer.h"

ForceDebugRenderer::ForceDebugRenderer() : VAO(0), VBO(0){
	// Create shader objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Set VAO and VBO for use
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Define pointers to attributes
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind buffer and array
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}