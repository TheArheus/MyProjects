//
// Created by Артём on 28.12.2017.
//

#include "Shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLenum CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string &fileName) {
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.txt"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i<SHADERS_NUMBER; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Shader program failed to link");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program is invalid");
}

Shader::~Shader() {
    glDeleteProgram(m_program);

    for(unsigned int i = 0; i<SHADERS_NUMBER; i++){
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr<<"Shader can not be created"<<std::endl;

    const GLchar* shaderCourceString[1];
    GLint  shaderCourceStringLength[1];
    shaderCourceString[0] = text.c_str();
    shaderCourceStringLength[0] = text.length();

    glShaderSource(shader, 1, shaderCourceString, shaderCourceStringLength);
    glCompileShader(shader);
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compile error");

    return shader;
}

void Shader::Bind() {
    glUseProgram(m_program);
}

static std::string LoadShader(const std::string& fileName){
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open()){
        while(file.good()){
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else{
        std::cerr<<"Unable to read file"<<std::endl;
    }
    return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE){
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr<<errorMessage<<": '"<<error<<"'"<<std::endl;
    }
}