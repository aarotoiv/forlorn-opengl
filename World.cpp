#include "World.h"
World::World() {
    worldBlocks.push_back(*new Block(-0.5f, -0.4f, 1.5f, -0.2f));
    worldBlocks.push_back(*new Block(1.5f, -0.4f, 1.5f, -0.2f));
}
World::~World() {

}
void World::update() {

}
void World::draw(glm::mat4 projection, float xPos, float yPos) {
    for(int i = 0; i<worldBlocks.size(); i++) {
        Block block = worldBlocks[i];
        block.draw(projection, xPos, yPos);
    }
}

Collisions World::checkCollisions(float xPos, float yPos, float width, float height) {
    Collisions collisions;
    collisions.bottom = 0.0f;
    collisions.left = 0.0f;
    collisions.top = 0.0f;
    collisions.right = 0.0f;
    //all colliders have x, y, w, h
    float colliders[1][4] = {
        //bottom
        {xPos + width / 2, yPos, width, height}
    };
    
    for(int i = 0; i<worldBlocks.size(); i++) {
        Block block = worldBlocks[i];
        float bottomCollision = block.checkCollisions(colliders[0][0], colliders[0][1], colliders[0][2], colliders[0][3]);
        if(collisions.bottom < bottomCollision) 
            collisions.bottom = bottomCollision;
    }
    return collisions;
}