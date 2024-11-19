#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader {
    public:
        // The program ID
        unsigned int ID;

        // Constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath);
    
        // Use/activate the shader
        void use();
    
        // Utility functions for shader uniform
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMatrix4fv(const std::string& name, const glm::mat4& trans) const;

    private:
        // Helper methods for creating shaders
        int createShader(GLenum shaderType, const char* shaderSource);
        int createShaderProgram(int vertexShader, int fragmentShader);
};

#endif