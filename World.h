#ifndef World_h
#define World_h

#include <iostream>
#include <vector>

#include "Block.h"

struct Collisions {
    float left, top, right, bottom;
};

class World {
    public:
        World();
        void draw(glm::mat4 projection, float xPos, float yPos);
        void update();
        Collisions checkCollisions(float xPos, float yPos, float width, float height);

        ~World();

    private:
        std::vector<Block> worldBlocks;

};

#endif