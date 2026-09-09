#ifndef GRAVITY_H
#define GRAVITY_H

#include "force.h"

#pragma once
class Gravity : public Force {
public:
	Gravity(Object* object, float gravity);

	void apply();
	std::vector<glm::vec3> getDebugVector();

private:
	Object* object;
	float gravity;
};

#endif