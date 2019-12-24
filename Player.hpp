#ifndef Player_h
#define Player_h

#include "Mesh.h"
#include "Shader.h"
#include "Spell.hpp"
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
        float GetScale();
        float GetRawBottom();
        float YPosForDraw();

        void HandleKeyDown(std::string key);
        void HandleKeyUp(std::string key);

        void HandleCollisions(float bottom, float left, float top, float right);

        void attemptJump();

    private:
        Mesh *theMesh;
        Shader *theShader;   

        Mesh *handMesh;
        Shader *handShader;

        Spell *rightSpell;
        Spell *leftSpell;
        
        GLuint uniformModel, uniformProjection, uniformView;
        //drawing lowest y
        float bottomY = -0.5f;
        //actualy x and y coords
        float xPos, yPos;
        //base sizes
        float baseWidth = 0.35f, baseHeight = 0.7f;
        //player scale, transforms player scale
        float scale = 0.4;
        //momentums
        float xMom;
        float yMom;
        //maximum fall momentum
        float yMomCap = 0.07f;
        //direction in which the player is going (for rendering mostly)
        bool direction;
        //falling and jumping
        bool falling;
        bool jumping;

        float jumpCap = 0.1f;
        float jumpHeight;

        //pretty 
        bool goingLeft, goingRight;
        bool tryingToJump;

        //spawn coords
        float spawnX = 0.0f;
        float spawnY = -1.0f;
};

#endif