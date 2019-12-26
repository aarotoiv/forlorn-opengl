#include "Spell.hpp"

Spell::Spell(int spellType) {
    type = spellType;
    x = 0;
    y = 0;
    attached = true;
    moveDir = 0;

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
    uniformColor = 0;
    uniformAlpha = 0;
}
Spell::Spell(int spellType, float xPos, float yPos, int direction, bool isAttached) {
    type = spellType;
    x = xPos;
    y = yPos;
    moveDir = direction;
    attached = isAttached;

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
    uniformColor = 0;
    uniformAlpha = 0;
}

Spell::~Spell() {}

void Spell::draw(glm::mat4 projectionMatrix, float middleX, float middleY, float playerScale, Shader* shader, Mesh* mesh) {
    shader->UseShader();
    uniformProjection = shader->GetProjectionLocation();
    uniformModel = shader->GetModelLocation();
    uniformColor = shader->GetColorLocation();
    uniformAlpha = shader->GetAlphaLocation();
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(0.0f + middleX * playerScale, 0.0f + middleY * playerScale, -2.5f));
    model = glm::scale(model, glm::vec3(spellScale, spellScale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    if(type == 1)
        glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
    if(type == 2) 
        glUniform3f(uniformColor, 0.0f, 1.0f, 0.0f);
    glUniform1f(uniformAlpha, 0.6f);
    mesh->RenderMesh();
    glUseProgram(0);
}

void Spell::draw(glm::mat4 projectionMatrix, float playerX, float playerY, Shader* shader, Mesh* mesh) {
    shader->UseShader();
    uniformProjection = shader->GetProjectionLocation();
    uniformModel = shader->GetModelLocation();
    uniformColor = shader->GetColorLocation();
    uniformAlpha = shader->GetAlphaLocation();
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(x - playerX, y + playerY, -2.5f));
    model = glm::scale(model, glm::vec3(spellScale, spellScale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    if(type == 1)
        glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
    if(type == 2) 
        glUniform3f(uniformColor, 0.0f, 1.0f, 0.0f);
    glUniform1f(uniformAlpha, 0.6f);
    mesh->RenderMesh();
    glUseProgram(0);

}
void Spell::update(double updateRate) {
    x += moveSpeed * updateRate * moveDir;
} 
void Spell::launch(float xPos, float yPos, int direction) {
    attached = false;
    x = xPos;
    y = yPos;
    moveDir = direction;
}
Seed* Spell::getSeed(float xPos, float yPos, int direction, bool isAttached) {
    Seed* seed = new Seed();
    seed->type = type;
    seed->x = xPos;
    seed->y = yPos;
    seed->moveDir = direction;
    seed->attached = isAttached;
    return seed;
}
