#ifndef Spell_hpp
#define Spell_hpp

#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext.hpp"

class Spell {
    public:
        Spell(int spellType);
        ~Spell();
        void draw(glm::mat4 projectionMatrix, float middleX, float middleY, float playerScale);
        void draw(glm::mat4 projectionMatrix, float playerX, float playerY);
        void update(double updateRate);
        void launch(float xPos, float yPos, int direction);
    private:
        GLuint uniformProjection, uniformModel, uniformView, uniformColor, uniformAlpha;
        Mesh *theMesh;
        Shader *theShader;
        float x, y;
        bool attached;
        int type;
        int moveDir;
        const float moveSpeed = 1.0f;
        const float spellScale = 0.4f;
};

#endif