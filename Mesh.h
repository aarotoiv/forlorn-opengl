#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>
#include <iostream>

class Mesh {
    public:
        Mesh();
        void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, GLfloat* colors, unsigned int numOfColors);
        void RenderMesh();
        void ClearMesh();

        ~Mesh();
    private:
        GLuint VAO, VBO, IBO, CBO;
        GLsizei indexCount;
};

#endif