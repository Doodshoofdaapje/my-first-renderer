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

class MeshRenderer : public Component{
    public:
        MeshRenderer(const char* objectPath, const char* texturePath, bool isTextured);

        void bind();
        void draw(Shader* shader, Transform* transform);

    private:
        // Model data
        ModelFileParser* parser;
        std::vector<float> vertexData; // Pos, Tex, Normal
        std::vector<int> indices;

        int textureSize;
        int vertexSize;

        // OpenGl Objects
        unsigned int VAO, EBO;
        const char* texturePath;

        // Properties
        bool textured;

        // Auxilaury methods
        int createTexture();
};

#endif