#ifndef FORCE_H
#define FORCE_H

#include "object.h"
#include "rigid_body.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#pragma once

class Force {
public:
	virtual ~Force() = default;
	virtual void apply() = 0;
	virtual void draw() = 0;
};

#endif
