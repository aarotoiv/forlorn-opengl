#include "Player.hpp"

Player::Player() {
    xPos = spawnX;
    yPos = spawnY + bottomY;
    xMom = 0.0f;
    yMom = 0.0f;
    direction = true;

    falling = true;
    jumping = false;
    jumpHeight = 0.0f;

    goingLeft = false;
    goingRight = false;
    tryingToJump = false;

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    rightSpell = new Spell(1);
    leftSpell = new Spell(2);


    //gl_Position = projection * view * model * vec4(pos, 1.0)

    unsigned int handIndices[] = {
        0, 1, 2,
        0, 2, 3
    };  
    
    GLfloat handVertices[] = {
        0.0f, bottomY + 0.325f, 1.0f, 
        0.150f, bottomY + 0.325f, 1.0f,
        0.150f, bottomY + 0.175f, 1.0f,
        0.0f, bottomY + 0.175f, 1.0f
    };

    handMesh = new Mesh();
    handMesh->CreateMesh(handVertices, handIndices, 12, 6, NULL, 0);
    handShader = new Shader();
    handShader->CreateFromFiles("Shaders/singleCol.vert", "Shaders/shader.frag");


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
        14, 16, 17
    };
    
    GLfloat vertices[] = {
        //body
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
        -0.15f, bottomY + 0.4f, 1.0f
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
        1.0, 220.0f / 255.0f, 177.0f / 255.0f
    };

    theMesh = new Mesh();
    //vertex count, index count, colorcount
    theMesh->CreateMesh(vertices, indices, 54, 30, colors, 54);
    theShader = new Shader();
    theShader->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");

}
void Player::Draw(glm::mat4 projectionMatrix) {
    int scaleDirectionMod = direction ? 1 : -1;
    //backhand
    handShader->UseShader();
    uniformProjection = handShader->GetProjectionLocation();
    uniformModel = handShader->GetModelLocation();
    glm::mat4 handFirst(1.0);
    handFirst = glm::translate(handFirst, glm::vec3(0.045f*scale * scaleDirectionMod, 0.0f, -2.5f));
    handFirst = glm::scale(handFirst, glm::vec3(scaleDirectionMod * scale, scale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(handFirst));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3f(handShader->GetColorLocation(), 227.0f/255.0f, 161.0f/255.0f, 115.0f/255.0f);
    glUniform1f(handShader->GetAlphaLocation(), 1.0);

    handMesh->RenderMesh();

    if(direction) {
        if(leftSpell != nullptr) {
            leftSpell->draw(projectionMatrix, 0.120f, bottomY + 0.25f, scale);
        }
    } else {
        if(rightSpell != nullptr) {
            rightSpell->draw(projectionMatrix, -0.120f, bottomY + 0.25f, scale);
        }
    }

    //body
    theShader->UseShader();
    uniformProjection = theShader->GetProjectionLocation();
    uniformModel = theShader->GetModelLocation();
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::scale(model, glm::vec3(scaleDirectionMod * scale, scale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    

    theMesh->RenderMesh();

    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    //tophand
    handShader->UseShader();
    uniformProjection = handShader->GetProjectionLocation();
    uniformModel = handShader->GetModelLocation();
    glm::mat4 hand(1.0);
    hand = glm::translate(hand, glm::vec3(0.0f, 0.0f, -2.5f));
    hand = glm::scale(hand, glm::vec3(scaleDirectionMod * scale, scale, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(hand));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3f(handShader->GetColorLocation(), 1.0f, 220.0f/255.0f, 177.0f/255.0f);
    glUniform1f(handShader->GetAlphaLocation(), 1.0);

    handMesh->RenderMesh();
    
    glUseProgram(0);

    if(direction) {
        if(rightSpell != nullptr) {
            rightSpell->draw(projectionMatrix, 0.075f, bottomY + 0.25f, scale);
        }
    }
    else {
        if(leftSpell != nullptr) {
            leftSpell->draw(projectionMatrix, -0.075f, bottomY + 0.25f, scale);
        }
    }
}


void Player::Update(double updateRate) {
    if(falling && yMom < yMomCap && !jumping) {
        yMom += 0.02f * updateRate;
    } else if(jumping) {
        yMom = -1.5f * updateRate;
        jumpHeight -= yMom;
        if(jumpHeight >= jumpCap) {
            jumping = false;
            jumpHeight = 0.0f;
        }
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
    
    if(tryingToJump)
        attemptJump();
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
float Player::GetScale() {
    return scale;
}
float Player::GetRawBottom() {
    return bottomY;
}
float Player::YPosForDraw() {
    return yPos + bottomY * scale;
}

void Player::HandleKeyDown(std::string key) {
    if(key == "left") {
        goingLeft = true;
    }
    if(key == "right") {
        goingRight = true;
    }
    if(key == "space") 
        tryingToJump = true;
}

void Player::HandleKeyUp(std::string key) {
    if(key == "left") {
        goingLeft = false;
    }
    if(key == "right") {
        goingRight = false;
    }
    if(key == "space")
        tryingToJump = false;
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

void Player::attemptJump() {
    if(!falling && !jumping) {
        jumping = true;
    }
}
