#include "Spell.hpp"

Spell::Spell(int spellType) {
    type = spellType;
    x = 0;
    y = 0;
    attached = true;

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
    uniformColor = 0;
    uniformAlpha = 0;

    unsigned int indices[] = {
        0, 1, 2, 
        0, 3, 2
    };

    float coords[] = {
        -0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 1.0f
    };

    theMesh = new Mesh();
    theMesh->CreateMesh(coords, indices, 12, 6, NULL, 0);

    theShader = new Shader();
    theShader->CreateFromFiles("Shaders/singleCol.vert", "Shaders/shader.frag");
}
Spell::~Spell() {

}
void Spell::draw(glm::mat4 projectionMatrix, float middleX, float middleY, float playerScale) {
    theShader->UseShader();
    uniformProjection = theShader->GetProjectionLocation();
    uniformModel = theShader->GetModelLocation();
    uniformColor = theShader->GetColorLocation();
    uniformAlpha = theShader->GetAlphaLocation();
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(0.0f + middleX * playerScale, 0.0f + middleY * playerScale, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    if(type == 1)
        glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
    if(type == 2) 
        glUniform3f(uniformColor, 0.0f, 1.0f, 0.0f);
    glUniform1f(uniformAlpha, 0.6f);
    theMesh->RenderMesh();
    glUseProgram(0);
}
void Spell::update(bool isAttached, float xPos, float yPos) {
    x = xPos;
    y = yPos;
    attached = isAttached;
}   
