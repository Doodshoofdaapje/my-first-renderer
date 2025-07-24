#version 460 core

#define MAX_LIGHTS 8

in vec3 P;
in vec3 N;
in vec2 TexCoord;

uniform vec3 viewPos;

uniform sampler2D ourTexture;
uniform bool textured;

uniform int numLights;

struct Light {
    vec3 position;
    vec3 color;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float kConstant;
    float kLinear;
    float kQuadratic;
};
uniform Light lights[MAX_LIGHTS];

struct Material {
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   float shininess;
} material;

out vec4 FragColor;
 
float cosAngle(vec3 a, vec3 b) {
    return max(dot(a, b) / (length(a) * length(b)), 0);
}

vec4 shading(vec3 P, vec3 N, Light light, Material mat)
{	
    vec3 normal = normalize(N);

    vec3 lightDir = normalize(light.position - P);
    vec3 reflectedLightDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - P);
    
    float diff = cosAngle(normal, lightDir);
    float spec = pow(cosAngle(viewDir, reflectedLightDir), material.shininess);

    vec4 diffuseLight = mat.diffuse * light.diffuse * diff;
    vec4 specularLight = mat.specular * light.specular * spec;
    vec4 ambientLight = mat.ambient * light.ambient;
    
	vec4 totalLight = vec4(0);
    totalLight += diffuseLight;
    totalLight += specularLight;
    totalLight += ambientLight;

    float distanceToLight = length(light.position - P);
    float attenuation = 1.0 / (light.kConstant + light.kLinear * distanceToLight + light.kQuadratic * (distanceToLight * distanceToLight)); 
    
	vec4 result  = totalLight * attenuation;

	return result;
}

vec4 totalShading(vec3 P, vec3 N, Material mat) {
    vec4 totalLight = vec4(0);

    for (int i = 0; i < numLights; i++) {
        totalLight += shading(P, N, lights[i], mat);
    }

    return totalLight;
}

void main()
{
    material.shininess = 1;
    material.ambient=vec4(0.1);
    material.diffuse=vec4(0.7);
    material.specular=vec4(0.4);

    vec4 baseColor = vec4(1.0);  // default color
    if (textured) {
        baseColor = texture(ourTexture, TexCoord);
    }

    FragColor = totalShading(P, N, material) * baseColor;
    
};