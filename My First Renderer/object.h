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

class Object {
    public:
        // Constructor parses object
        Object(const char* objectPath);

        void bind();
        void draw();
        unsigned int getFaceCount();

    private:
        // Model data
        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<float>> textureCoords;
        std::vector<std::vector<float>> vertexNormals;
        std::vector<std::vector<float>> faces;

        std::vector<unsigned int> VAO;

        float x, y, z;
        float rotation;

        // Auxilaury methods
        void parseLine(const std::string& str);
        std::vector<std::string> splitOn(const std::string& str, const std::string& delimiter);
        void bindFace(unsigned int FaceVAO, const std::vector<float>& face);
        int createTexture(const char* filepath);
};

#endif