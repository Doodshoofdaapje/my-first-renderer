#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform float time;

out vec2 TexCoord;
out vec3 Normal;

void main()
{
   float offset = sin(time);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TexCoord = aTexCoord;
   Normal = aNormal;
};