#ifndef FORCE_H
#define FORCE_H

#include "object.h"
#include "rigid_body.h"

#pragma once

class Force {
public:
	virtual ~Force() = default;
	virtual void apply() = 0;
	virtual std::vector<glm::vec3> getDebugVector() = 0;
};

#endif
