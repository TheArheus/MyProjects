#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

GLuint MakeShaderProgram(std::string vertex, std::string fragment);
std::string GetFile(std::string filePath);

int main(int argc, char* argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 720, "Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    glewInit();

    GLuint ShaderProgram = MakeShaderProgram("C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Vertex.vs", "C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Frag.fs");

    float triangle1[] = {-0.1f, -0.5f,
                        -0.5f, -0.2f,
                        0.1f, -0.1f};

    float triangle2[] = {-0.5f, 0.1f,
                         0.5f, 0.9f,
                         0.2f, 0.1f};

    float color1[] = {0.5, 0.1, 0.3};
    float color2[] = {0.1, 0.8, 0.5};

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glUseProgram(ShaderProgram);

    do{
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }while(!glfwWindowShouldClose(window));

    return 0;
}

std::string GetFile(std::string filePath){
    std::string output;
    std::string line;
    std::ifstream FILE;
    FILE.open(filePath, std::ios_base::in);
    if(FILE.good()){
        while(std::getline(FILE, line)){
            output += line;
            output += "\n";
        }
    }

    FILE.close();

    return output;
}

GLuint MakeShaderProgram(std::string vertex, std::string fragment){
    std::string vertexStr = GetFile(vertex);
    std::string fragmentStr = GetFile(fragment);

    const char* vertexSrc = vertexStr.c_str();
    const char* fragmentSrc = fragmentStr.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

