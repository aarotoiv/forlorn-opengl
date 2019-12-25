#ifndef World_h
#define World_h

#include <iostream>
#include <vector>

#include "Spell.hpp"

#include "Block.h"

struct Collisions {
    float left, top, right, bottom;
};

class World {
    public:
        World();
        void draw(glm::mat4 projection, float xPos, float yPos);
        void update(double updateRate);
        Collisions checkCollisions(float xPos, float yPos, float width, float height);

        void spellLaunch(Spell* launchedSpell);

        ~World();

    private:
        std::vector<Block> worldBlocks;
        std::vector<Spell*> spells;
};

#endif