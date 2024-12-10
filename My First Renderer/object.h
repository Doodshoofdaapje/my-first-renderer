#ifndef OBJECT_H
#define OBJECT_H

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
#include "ModelFileParser.h"
#include "ObjModelParser.h"
#include "shader.h"
#include "Transform.h"

class Object {
    public:
        Object(const char* objectPath, const char* texturePath, bool isTextured, const Transform& trans);

        void bind();
        void draw(Shader* shader);

    private:
        // Model data
        ModelFileParser* parser;
        std::vector<float> vertexData; // Pos, Tex, Normal
        std::vector<int> indices;

        // OpenGl Objects
        unsigned int VAO, EBO;
        const char* texturePath;

        // Properties
        Transform transform; 
        bool textured;

        // Auxilaury methods
        int createTexture();
};

#endif