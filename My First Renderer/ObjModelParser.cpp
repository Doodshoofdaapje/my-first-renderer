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
    textureSize = 2;

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
        std::cout << e.what() << std::endl;
        std::cout << "ERROR::PARSER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void ObjModelParser::parseLine(const std::string& str) {
    std::string strCleaned = splitOn(str, " #")[0];
    std::vector<std::string> words = splitOnWhiteSpaces(strCleaned);
    if (words.empty()) {
        return;
    }

    std::string keyWord = words[0];

    auto parseVector = [&](const size_t size) {
        std::vector<float> vector(size);
        for (size_t i = 0; i < size; ++i) {
            vector[i] = std::stof(words[i+1]);
        }
        return vector;
        };

    if (keyWord == "v") {
        vertices.push_back(parseVector(3));
    }
    else if (keyWord == "vt") {
        if (words.size() == 4 && textureSize != 3) {
            textureSize = 3;
        }
        textureCoords.push_back(parseVector(textureSize)); // TODO: handle texture coords of vec3
    }
    else if (keyWord == "vn") {
        vertexNormals.push_back(parseVector(3));
    }
    else if (keyWord == "f") {
        // In case more than 3 points specified we triangulate the n-polygon
        for (size_t i = 3; i < words.size(); ++i) {
            parseFace({ words[1], words[i-1], words[i] });
        };
    }
}

void ObjModelParser::parseFace(const std::vector<std::string>& words) {
    for (size_t i = 0; i < words.size(); ++i) {
        // Vertex exists
        std::string vertex = words[i];
        if (vertexMap.find(vertex) != vertexMap.end()) {
            indices.push_back(vertexMap[vertex]);
            continue;
        }

        // Vertex doesnt exists
        std::vector<std::string> faceIndices = splitOn(vertex, "/");
   
        // Vertex position
        int vertexIndex = std::stoi(faceIndices[0]) - 1;
        vertexData.insert(vertexData.end(), vertices[vertexIndex].begin(), vertices[vertexIndex].end());

        // Vertex texture coords, default (0, 0)
        if (faceIndices.size() > 1 && !faceIndices[1].empty()) {
            int textureIndex = std::stoi(faceIndices[1]) - 1;
            vertexData.insert(vertexData.end(), textureCoords[textureIndex].begin(), textureCoords[textureIndex].end());
        }
        else {
            vertexData.insert(vertexData.end(), { 0.0f, 0.0f });  // default texture coord
        }
        
        // Vertex normals, default (0, 0, 0)
        if (faceIndices.size() > 2 && !faceIndices[2].empty()) {
            int normalIndex = std::stoi(faceIndices[2]) - 1;
            vertexData.insert(vertexData.end(), vertexNormals[normalIndex].begin(), vertexNormals[normalIndex].end());
        }
        else {
            vertexData.insert(vertexData.end(), { 0.0f, 0.0f, 0.0f });  // default normal
        }
        
        int index = vertexData.size() / (6 + textureSize) - 1;
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

int ObjModelParser::getTextureSize() {
    return textureSize;
}