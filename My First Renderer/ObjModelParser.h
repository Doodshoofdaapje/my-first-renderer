#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "ModelFileParser.h"

class ObjModelParser : public ModelFileParser {
    public:
        ObjModelParser();
        void parse(const char* objectPath);
        std::vector<float> getVertexData();
        std::vector<int> getIndices();

    private:
        std::unordered_map<std::string, int> vertexMap;
        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<float>> textureCoords;
        std::vector<std::vector<float>> vertexNormals;
        std::vector<float> vertexData;
        std::vector<int> indices;

        void parseLine(const std::string& str);
        void parseFace(const std::vector<std::string>& words);

        std::vector<std::string> splitOn(const std::string& str, const std::string& delimiter) {
            std::vector<std::string> substrings;
            std::string substring;
            size_t pos = 0;
            size_t nextPos;

            while ((nextPos = str.find(delimiter, pos)) != std::string::npos) {
                substring = str.substr(pos, nextPos - pos);
                substrings.push_back(substring);
                pos = nextPos + delimiter.length();
            }

            // Add the remaining part of the string (after the last delimiter)
            substrings.push_back(str.substr(pos));

            return substrings;
        };
};

#endif