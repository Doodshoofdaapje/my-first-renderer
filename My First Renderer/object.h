#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "stb_image.h"
#include "model_file_parser.h"
#include "obj_model_parser.h"
#include "shader.h"
#include "transform.h"

class Object {
public:
    virtual ~Object() = default;
    glm::vec3 getPosition() const { return transform.position; }
    glm::vec3 getRotation() const { return transform.rotation; }
    glm::vec3 getScale()    const { return transform.scale; }

protected:
    Transform transform;

};

#endif