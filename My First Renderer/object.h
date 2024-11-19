#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>

#include "stb_image.h"
#include "ModelFileParser.h"
#include "ObjModelParser.h"

class Object {
    public:
        Object(const char* objectPath);

        void bind();
        void draw();

    private:
        // Model data
        ModelFileParser* parser;
        std::vector<float> vertexData; // Pos, Tex, Normal
        std::vector<int> indices;

        unsigned int VAO, EBO;

        float x, y, z;
        float rotation;

        // Auxilaury methods
        int createTexture(const char* filepath);
};

#endif