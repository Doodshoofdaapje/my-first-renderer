#include "ObjModelParser.h"

ObjModelParser::ObjModelParser() {
    // Temporary, TODO: Change to local variables to release data after parsing
    vertices = {};
    textureCoords = {};
    vertexNormals = {};

    // Main data
    vertexMap = {};
    vertexData = {};
    indices = {};

    return;
}

void ObjModelParser::parse(const char* objectPath) {
    // Allow object file to throw exceptions
    std::ifstream objectFile;
    objectFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open file
        objectFile.open(objectPath);

        std::string line;
        while (std::getline(objectFile, line)) {
            parseLine(line);
        }

        objectFile.close();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::PARSER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void ObjModelParser::parseLine(const std::string& str) {
    std::vector<std::string> words = splitOn(str, " ");
    if (words.empty()) {
        return;
    }

    std::string keyWord = words[0];

    auto parseVector = [&](const size_t size) {
        std::vector<float> vector(size);
        for (size_t i = 1; i < words.size(); ++i) {
            vector[i - 1] = std::stof(words[i]);
        }
        return vector;
        };

    if (keyWord == "v") {
        vertices.push_back(parseVector(3));
    }
    else if (keyWord == "vt") {
        textureCoords.push_back(parseVector(2));
    }
    else if (keyWord == "vn") {
        vertexNormals.push_back(parseVector(3));
    }
    else if (keyWord == "f") {
        parseFace(words);
    }
}

void ObjModelParser::parseFace(const std::vector<std::string>& words) {
    for (size_t i = 1; i < words.size(); ++i) {
        // Vertex exists
        std::string vertex = words[i];
        if (vertexMap.find(vertex) != vertexMap.end()) {
            indices.push_back(vertexMap[vertex]);
            continue;
        }

        // Vertex doesnt exists
        std::vector<std::string> faceIndices = splitOn(vertex, "/");
   
        int vertexIndex = std::stoi(faceIndices[0]) - 1;
        int textureIndex = std::stoi(faceIndices[1]) - 1;
        int normalIndex = std::stoi(faceIndices[2]) - 1;

        vertexData.insert(vertexData.end(), vertices[vertexIndex].begin(), vertices[vertexIndex].end());
        vertexData.insert(vertexData.end(), textureCoords[textureIndex].begin(), textureCoords[textureIndex].end());
        vertexData.insert(vertexData.end(), vertexNormals[normalIndex].begin(), vertexNormals[normalIndex].end());

        int index = vertexData.size() / 8 - 1;
        vertexMap[vertex] = index;
        indices.push_back(index);
    }
}

std::vector<float> ObjModelParser::getVertexData() {
    return vertexData;
}

std::vector<int> ObjModelParser::getIndices() {
    return indices;
}