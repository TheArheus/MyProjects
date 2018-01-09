//
// Created by Артём on 28.12.2017.
//

#ifndef SDL_SHADER_H
#define SDL_SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& filePath);
    ~Shader();

    void Bind();

private:
    static const unsigned int SHADERS_NUMBER = 2;
    GLuint m_program;
    GLuint m_shaders[SHADERS_NUMBER];
};


#endif //SDL_SHADER_H
