#include "light_source.h"

LightSource::LightSource() {
	this->ambient = glm::vec4(0.1f, 0.5f, 0.1f, 1.0f);
	this->diffuse = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	this->specular = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	this->kConstant = 1.0f;
	this->kLinear = 0.7f;
	this->kQuadratic = 1.8f;
}

LightSource::LightSource(const glm::vec4& ambient,
					 	 const glm::vec4& diffuse,
					  	 const glm::vec4& specular,
						 const float kConstant,
						 const float kLinear,
						 const float kQuadratic) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;

	this->kConstant = kConstant;
	this->kLinear = kLinear;
	this->kQuadratic = kQuadratic;
}

glm::vec4 LightSource::getAmbient() {
	return ambient;
}

glm::vec4 LightSource::getDiffuse() {
	return diffuse;
}

glm::vec4 LightSource::getSpecular() {
	return specular;
}

float LightSource::getKConstant() {
	return kConstant;
}

float LightSource::getKLinear() {
	return kLinear;
}

float LightSource::getKQuadratic() {
	return kQuadratic;
}


