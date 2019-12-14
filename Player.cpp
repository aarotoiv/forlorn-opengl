#include "Player.hpp"

Player::Player() {
    xPos = spawnX;
    yPos = spawnY + bottomY;
    xMom = 0.0f;
    direction = true;

    falling = true;

    goingLeft = false;
    goingRight = false;


    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    //gl_Position = projection * view * model * vec4(pos, 1.0)

    unsigned int indices[] = {
        //BODY (4 * 3 = 12)
        0, 1, 2,
        0, 3, 1,
        0, 3, 4,
        4, 5, 3,

        //leftleg (6)
        6, 7, 8,
        6, 8, 9,
        
        //rightleg (6)
        10, 11, 12,
        10, 12, 13,

        //head (6)
        14, 15, 16,
        14, 16, 17,
        
        //hand
        18, 19, 20,
        18, 20, 21

    };
    
    GLfloat vertices[] = {
        //BODY (6 * 3 = 18)
        -0.075f, bottomY + 0.4f, 1.0f,
        -0.075f, bottomY + 0.05f, 1.0f,
        -0.125f, bottomY + 0.35f, 1.0f,
        0.075f, bottomY + 0.05f, 1.0f,
        0.025f, bottomY + 0.4f, 1.0f,
        0.125f, bottomY + 0.35f, 1.0f,

        //leftleg (12)
        -0.065f, bottomY + 0.05f, 1.0f,
        -0.010f, bottomY + 0.05f, 1.0f,
        -0.010f, bottomY +0.0f, 1.0f,
        -0.065f, bottomY + 0.0f, 1.0f,
        //rightleg(12)
        0.065f, bottomY + 0.05f, 1.0f,
        0.010f, bottomY + 0.05f, 1.0f,
        0.010f, bottomY + 0.0f, 1.0f,
        0.065f, bottomY + 0.0f, 1.0f,
        //Head(12)
        -0.15f, bottomY + 0.7f, 1.0f,
        0.175f, bottomY + 0.7f, 1.0f,
        0.175f, bottomY + 0.36f, 1.0f,
        -0.15f, bottomY + 0.4f, 1.0f,
        //hand
        0.025f, bottomY + 0.325f, 1.0f, 
        0.175f, bottomY + 0.325f, 1.0f,
        0.175f, bottomY + 0.175f, 1.0f,
        0.025f, bottomY + 0.175f, 1.0f

    };
    GLfloat colors[] = {
        //BODY (6 * 3 = 18)
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,

        //leftleg (12)
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,

        //rightleg(12)
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,

        //head
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,

        //hand
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f,
        1.0, 220.0f / 255.0f, 177.0f / 255.0f

    };

    theMesh = new Mesh();
    //vertex count, index count, colorcount
    theMesh->CreateMesh(vertices, indices, 66, 36, colors, 66);
    theShader = new Shader();
    theShader->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
}
/*void Player::DrawLimb(GLfloat* vertices, unsigned int* indices, glm::vec3 color) {
    theMesh->CreateMesh(vertices, indices, 12, 6);
    theShader->UseShader();
    GLuint uniformColor = theShader->GetColorLocation();
    glUniform4fv(uniformColor, 1, GL_FALSE, glvec3::value_ptr(color));
    theMesh->RenderMesh();
}*/
void Player::Draw(glm::mat4 projectionMatrix) {
    int scaleDirectionMod = direction ? 1 : -1;
    //std::cout << "THEERROR " << glGetError() << std::endl;
    //std::cout << glm::to_string(projection) << std::endl;
    theShader->UseShader();
    uniformProjection = theShader->GetProjectionLocation();
    uniformModel = theShader->GetModelLocation();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::scale(model, glm::vec3(scaleDirectionMod * scale, scale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
    
    
    // works glUniform3f(theShader->GetColorLocation(), 1.0f, 1.0f, 1.0f);
    
    
    //HANDLE MATRIX STUFF
    theMesh->RenderMesh();
    
    glUseProgram(0);
}

void Player::Update(float updateRate) {
    if(falling && yMom < yMomCap) {
        yMom += 0.02f * updateRate;
    } else {
        yMom = 0.0f;
    }
    if(goingLeft) {
        xMom = -1.2f;
    }
    if(goingRight) {
        xMom = 1.2f;
    }
    if(!goingLeft && !goingRight) 
        xMom = 0;

    xPos += xMom * updateRate;
    yPos += yMom;

    if(xMom > 0) 
        direction = true;
    if(xMom < 0) 
        direction = false;
}




float Player::GetX() {
    return xPos;
}
float Player::GetBottom() {
    return yPos;
}
float Player::GetWidth() {
    return baseWidth * scale;
}
float Player::GetHeight() {
    return baseHeight * scale;
}
float Player::YPosForDraw() {
    return yPos + bottomY * scale;
}

void Player::HandleCollisions(float bottom, float left, float top, float right) {
    if(bottom > 0) {
        falling = false;
        yPos -= (bottom - 1);
        //std::cout << bottom << std::endl;
    } else {
        falling = true;
    }
}

void Player::HandleKeyDown(std::string key) {
    if(key == "left") {
        goingLeft = true;
    }
    if(key == "right") {
        goingRight = true;
    }
}

void Player::HandleKeyUp(std::string key) {
    if(key == "left") {
        goingLeft = false;
    }
    if(key == "right") {
        goingRight = false;
    }
}