#ifndef Spell_hpp
#define Spell_hpp

#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext.hpp"
struct Seed {
    int type;
    float x;
    float y;
    int moveDir;
    bool attached;
};

class Spell {
    public:
        Spell(int spellType);
        Spell(int spellType, float xPos, float yPos, int direction, bool isAttached);
        ~Spell();
        void draw(glm::mat4 projectionMatrix, float middleX, float middleY, float playerScale, Shader* shader, Mesh* mesh);
        void draw(glm::mat4 projectionMatrix, float playerX, float playerY, Shader* shader, Mesh* mesh);
        void update(double updateRate);
        void launch(float xPos, float yPos, int direction);

        Seed* getSeed(float xPos, float yPos, int direction, bool isAttached);

    private:
        GLuint uniformProjection, uniformModel, uniformView, uniformColor, uniformAlpha;
        float x, y;
        bool attached;
        int type;
        int moveDir;
        const float moveSpeed = 2.0f;
        const float spellScale = 0.3f;
};

#endif