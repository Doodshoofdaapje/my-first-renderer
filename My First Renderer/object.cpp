#include "object.h"

Object::Object(const char* objectPath, bool isTextured, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scaler) {
    // Start Parsing
    std::string path(objectPath);
    std::string fileExtention = path.substr(path.find_last_of("."));

    if (fileExtention == ".obj") {
        parser = new ObjModelParser();
    }
    else {
        std::cout << "ERROR::OBJECT::WRONG_FILE_FORMAT" << std::endl;
        return;
    }

    // Initialize class variables
    parser->parse(objectPath);
    vertexData = parser->getVertexData();
    indices = parser->getIndices();

    position = pos;
    rotation = rot;
    textured = isTextured;
    scale = scaler;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    delete parser;
}

void Object::bind() {
    // Bind to array
    glBindVertexArray(VAO);

    // Setup texture
    int texture = createTexture("doghuhwhat.jpeg");
    glBindTexture(GL_TEXTURE_2D, texture);

    // Object data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // EBO for efficient memory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    // Specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Specify texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Specify vertex normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind buffer and array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::draw(Shader* shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around z
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader->setBool("textured", textured);
    shader->setMatrix4fv("model", model);
    shader->setMatrix4fv("view", view);
    shader->setMatrix4fv("projection", projection);
    shader->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
        std::cout << "Generated texture" << std::endl;
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}