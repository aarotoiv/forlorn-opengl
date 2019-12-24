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
        void draw(glm::mat4 projectionMatrix, float playerX, float playerY, float playerScale);
        void update(bool isAttached, float xPos, float yPos);
    private:
        GLuint uniformProjection, uniformModel, uniformView, uniformColor, uniformAlpha;
        Mesh *theMesh;
        Shader *theShader;
        float x, y;
        bool attached;
        int type;
};

#endif