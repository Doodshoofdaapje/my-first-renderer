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
};
uniform Material material;

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
    
    float diff = cosAngle(lightDir, normal);
    float spec = pow(cosAngle(reflectedLightDir, viewDir), mat.shininess);
    
    vec3 ambientLight = mat.ambient.rgb * light.ambient.rgb;
    vec3 diffuseLight = mat.diffuse.rgb * diff * light.diffuse.rgb;
    vec3 specularLight = mat.specular.rgb * spec * light.specular.rgb;
    
	vec3 totalLight = ambientLight + diffuseLight + specularLight;

     float distanceToLight = length(light.position - P);
     float attenuation = 1.0 / (light.kConstant + light.kLinear * distanceToLight + light.kQuadratic * (distanceToLight * distanceToLight)); 
    
	vec3 result  = totalLight * attenuation;

	return vec4(result, mat.ambient.a);
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
    vec4 baseColor = vec4(1.0);  // default color
    if (textured) {
        baseColor = texture(ourTexture, TexCoord);
    }
    
    FragColor = vec4(totalShading(P,N,material).rgb * baseColor.rgb, baseColor.a);
};