#pragma once

#ifndef SPRING_H
#define SPRING_H

#include "force.h"

#pragma once
class Spring : public Force {
public:
	Spring(Object& obj1, Object& obj2, double dist, double ks, double kd);

	void apply();
	std::vector<glm::vec3> getDebugVector();

private:
	Object& obj1;   // particle 1
	Object& obj2;   // particle 2 
	double dist;     // rest length
	double ks, kd; // spring strength constants
};

#endif


