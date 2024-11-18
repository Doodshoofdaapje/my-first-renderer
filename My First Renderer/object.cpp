#include "object.h"

Object::Object(const char* objectPath) {
    vertices = {};
    textureCoords = {};
    vertexNormals = {};
    faces = {};

    x = 0.0f; y = 0.0f; z = 0.0f;
    rotation = 0.0f;

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
        std::cout << "ERROR::OBJECT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

    VAO.resize(faces.size());
    glGenVertexArrays(static_cast<GLsizei>(VAO.size()), VAO.data());
}

void Object::parseLine(const std::string& str) {
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

    } else if (keyWord == "vt") {
        textureCoords.push_back(parseVector(2));

    } else if (keyWord == "vn") {
        vertexNormals.push_back(parseVector(3));

    } else if (keyWord == "f") {
        std::vector<float> face = {};
        for (size_t i = 1; i < words.size(); ++i) {
            std::vector<std::string> indices = splitOn(words[i], "/");

            int vertexIndex = std::stoi(indices[0]) - 1;
            int textureIndex = std::stoi(indices[1]) - 1;
            int normalIndex = std::stoi(indices[2]) - 1;

            face.insert(face.end(), vertices[vertexIndex].begin(), vertices[vertexIndex].end());
            face.insert(face.end(), textureCoords[textureIndex].begin(), textureCoords[textureIndex].end());
            face.insert(face.end(), vertexNormals[normalIndex].begin(), vertexNormals[normalIndex].end());
        }
        faces.push_back(face);
    }
}

std::vector<std::string> Object::splitOn(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> substrings;
    std::string substring;
    size_t pos = 0;
    size_t nextPos;

    while ((nextPos = str.find(delimiter, pos)) != std::string::npos) {
        substring = str.substr(pos, nextPos-pos);
        substrings.push_back(substring);
        pos = nextPos + delimiter.length();
    }

    // Add the remaining part of the string (after the last delimiter)
    substrings.push_back(str.substr(pos));

    return substrings;
}

unsigned int Object::getFaceCount() {
    return faces.size();
}

void Object::bind() {
    for (size_t i = 0; i < faces.size(); i++) {
        bindFace(VAO[i], faces[i]);
    }
}

void Object::bindFace(unsigned int FaceVAO, const std::vector<float>& face) {
    // Bind to array
    glBindVertexArray(FaceVAO);

    // Setup texture
    int texture = createTexture("doghuhwhat.jpeg");
    glBindTexture(GL_TEXTURE_2D, texture);

    // Object data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, face.size() * sizeof(float), face.data(), GL_STATIC_DRAW);

    // Specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Specify texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Specify vertex normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind buffer and array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::draw() {
    for (size_t i = 0; i < VAO.size(); i++) {
        glBindVertexArray(VAO[i]);
        glDrawArrays(GL_TRIANGLES, 0, faces[i].size() / 8);
    }
}

int Object::createTexture(const char* filepath) {
    // Setup texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}