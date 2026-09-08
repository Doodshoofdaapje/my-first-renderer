#ifndef GRAVITY_H
#define GRAVITY_H

#include "force.h"

#pragma once
class Gravity : public Force {
public:
	Gravity(Object* object, float gravity);

	void apply();
	void draw();

private:
	Object* object;
	float gravity;
};

#endif