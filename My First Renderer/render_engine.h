#pragma once

#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>

#include "solver.h"
#include "object.h"
#include "gravity.h"
#include "light_source.h"
#include "camera.h"
#include "force_debug_renderer.h"

class RenderEngine {
	private:
		// Main generic shader program
		Shader shader;

		// Optional pointers to objecs to render
		std::vector<Object*> meshObjects;
		std::vector<Object*> lights;
		std::vector<Force*> forces;

		// Helper objects to save rendering states
		std::vector<ForceDebugRenderer> forcesDebugRenderers; // Index of debugRenderer must match index of force

		// Draw functions
		void updateLights();
		void drawMeshObjects();
		void drawForces();

	public:
		// Constructor and disable copying
		RenderEngine();
		RenderEngine(const RenderEngine&) = delete;
		RenderEngine& operator=(const RenderEngine&) = delete;
		
		// Setters for object references
		void setMeshObjects(const std::vector<Object*> meshObjects);
		void setLights(const std::vector<Object*> lights);
		void setForces(const std::vector<Force*> forces);

		// Main render loop
		void render(Camera& camera);

};

#endif