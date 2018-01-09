#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string GetFile(std::string filePath);

GLuint MakeShaderProgram(std::string vertex, std::string fragment);

float triangle1[] = {-0.1f, -0.5f,
                     -0.5f, -0.2f,
                     0.1f, -0.1f};

float triangle2[] = {-0.5f, 0.1f,
                     0.5f, 0.9f,
                     0.2f, 0.1f};

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1024, 720, "WINDOW", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewInit();

    GLuint program1, program2;
    program1 = MakeShaderProgram("C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Vertex.vs", "C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Frag.fs");
    program2 = MakeShaderProgram("C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Vertex.vs", "C:\\Users\\Asus\\CLionProjects\\OpenGL1\\Frag1.fs");

    GLuint VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    //  ================================
    //First Triangle
    //  ================================
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //  ================================
    //Second Triangle
    //  ================================
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program1);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(program2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glfwDestroyWindow(window);

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