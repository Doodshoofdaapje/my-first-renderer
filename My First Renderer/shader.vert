#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 P;
out vec3 N;

void main()
{
	mat4 ModelViewProjectMatrix = projection * view * model;
	mat4 ModelViewMatrix = view * model;
	mat3 NormalMatrix = transpose(inverse(mat3(ModelViewMatrix)));

	gl_Position = ModelViewProjectMatrix * vec4(aPos, 1.0); // Position in eye space
	
	P = vec3(model * vec4(aPos, 1)); // Posiiton in world space
	N = NormalMatrix * aNormal;

	TexCoord = aTexCoord;
	Normal = aNormal;
};