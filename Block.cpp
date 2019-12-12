#include "Block.h"

Block::Block(float xPos, float yPos, float blockWidth, float blockHeight) {
    x = xPos;
    y = -yPos;
    width = blockWidth;
    height = -blockHeight;

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    unsigned int indices[] = {
        0,1,2,
        0,3,2
    };

    float coords[] = {
        x, -y, 1.0f,
        x + width, -y, 1.0f,
        x + width, -y + -height, 1.0f,
        x, -y + -height, 1.0f
    };

    GLfloat colors[] = {
        1.0f, 1.0f, 1.0f, 
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 
        1.0f, 1.0f, 1.0f
    };

    theMesh = new Mesh();
    theMesh->CreateMesh(coords, indices, 12, 6, colors, 12);
    theShader = new Shader();
    theShader->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
    //IYSLS
    /*for(int i = 0; i<12; i++) {
        std::cout << coords[i] << std::endl;
    }*/
}
Block::~Block() {

}
void Block::update() {

}
void Block::draw(glm::mat4 projectionMatrix, float playerX, float playerY) {
    theShader->UseShader();
    uniformProjection = theShader->GetProjectionLocation();
    uniformModel = theShader->GetModelLocation();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f - playerX, 0.0f + playerY, -2.5f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    theMesh->RenderMesh();
    glUseProgram(0);
}

float Block::checkCollisions(float cX, float cY, float cW, float cH) {
    if(cX >= x && cX <= x + width + cW && cY >= y && cY <= y + height) {
        return 1.0f + cY - y;
    } else {
        return 0.0f;
    }
}