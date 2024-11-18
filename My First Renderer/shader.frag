#version 460 core

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform bool textured;

out vec4 FragColor;

void main()
{
    if (textured) {
        FragColor = texture(ourTexture, TexCoord);
    }
    else {
        FragColor = vec4(0.8, 0.1, 0.1, 1.0);
    }
    
};
