#ifndef Player_h
#define Player_h

#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext.hpp"


class Player {
    public:
        Player();
        void Draw(glm::mat4 projectionMatrix);
        void DrawLimb(GLfloat* vertices, unsigned int* indices, glm::vec4 color);
        void Update(double updateRate);
        ~Player();

        float GetX();
        float GetBottom();
        float GetWidth();
        float GetHeight();
        float YPosForDraw();

        void HandleKeyDown(std::string key);
        void HandleKeyUp(std::string key);

        void HandleCollisions(float bottom, float left, float top, float right);

    private:
        Mesh *theMesh;
        Shader *theShader;   
        GLuint uniformModel, uniformProjection, uniformView;
        float bottomY = -0.5f;
        float xPos, yPos;
        float baseWidth = 0.35f, baseHeight = 0.7f;
        float scale = 0.4;
        float xMom;
        float yMom;
        float yMomCap = 0.07f;
        
        bool direction;

        bool falling;

        bool goingLeft, goingRight;

        float spawnX = 0.0f;
        float spawnY = -1.0f;
};

#endif