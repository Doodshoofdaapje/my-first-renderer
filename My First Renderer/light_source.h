#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <vector>
#include <array>

#include "object.h"
#include "transform.h"

class LightSource : public Component {
public:
    LightSource();
    LightSource(const glm::vec3& color, 
                const glm::vec4& ambient, 
                const glm::vec4& diffuse, 
                const glm::vec4& specular,
                const float kConstant,
                const float kLinear,
                const float kQuadratic);

    glm::vec3 getColor();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();

    float getKConstant();
    float getKLinear();
    float getKQuadratic();

private:
    glm::vec3 color;
    
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;

    float kConstant;
    float kLinear;
    float kQuadratic;

};

#endif