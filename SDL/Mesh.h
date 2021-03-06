//
// Created by Артём on 31.12.2017.
//

#ifndef SDL_MESH_H
#define SDL_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{
public:
    Vertex(const glm::vec3& pos){
        this->pos = pos;
    }
private:
    glm::vec3 pos;
};

class Mesh {
public:
    Mesh(Vertex* vertices, unsigned int numVertices);
    ~Mesh();

    void Draw();
private:
    enum{
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    unsigned int m_drawCount;
};


#endif //SDL_MESH_H
