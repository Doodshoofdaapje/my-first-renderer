#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
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
#include "object.h"
#include "material.h"

class MeshRenderer : public Component{
    public:
        MeshRenderer(const char* objectPath);

        void setup();
        void draw(Shader* shader, Transform* transform);
        MeshRenderer* setTexture(bool isTextured, const char* texturePath);
        MeshRenderer* setMaterial(float shininess, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);

    private:
        // Model data
        ModelFileParser* parser;
        std::vector<float> vertexData; // Pos, Tex, Normal
        std::vector<int> indices;

        // Texture data
        const char* texturePath;
        int textureSize;
        int vertexSize;

        // Material data
        Material material;

        // OpenGl Objects
        unsigned int textureID;
        unsigned int VAO, EBO;

        // Properties
        bool textured;

        // Auxilaury methods
        int createTexture(const char* texturePath);
};

#endif