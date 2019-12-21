#ifndef Block_h
#define Block_h
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext.hpp"


class Block {
    public:
        Block(float x, float y, float w, float h);
        void draw(glm::mat4 projectionMatrix, float playerX, float playerY);
        void update();
        float checkCollisions(float cX, float cY, float cW, float cH);
        ~Block();

    private:
        float vertices[12];
        GLuint uniformProjection, uniformModel, uniformView;
        Mesh *theMesh;
        Shader *theShader;
        float x, y, width, height;
};

#endif