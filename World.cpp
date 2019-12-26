#include "World.h"
World::World() {
    worldBlocks.push_back(new Block(-0.5f, -0.4f, 1.5f, -0.2f));
    worldBlocks.push_back(new Block(1.5f, -0.4f, 1.5f, -0.2f));

    createSpellGraphics();
}
World::~World() {

}

void World::createSpellGraphics() {
    unsigned int indices[] = {
        0, 1, 2, 
        0, 3, 2
    };

    float coords[] = {
        -0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 1.0f
    };

    spellMesh = new Mesh();
    spellMesh->CreateMesh(coords, indices, 12, 6, NULL, 0);
    
    spellShader = new Shader();
    spellShader->CreateFromFiles("Shaders/singleCol.vert", "Shaders/shader.frag");
}

void World::update(double updateRate) {
    for(int i = 0; i<spells.size(); i++) {
        spells[i]->update(updateRate);
    }
}
void World::draw(glm::mat4 projection, float xPos, float yPos) {
    for(int i = 0; i<worldBlocks.size(); i++) {
        worldBlocks[i]->draw(projection, xPos, yPos);
    }
    for(int i = 0; i<spells.size(); i++) {
        spells[i]->draw(projection, xPos, yPos, spellShader, spellMesh);
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
        float bottomCollision = worldBlocks[i]->checkCollisions(colliders[0][0], colliders[0][1], colliders[0][2], colliders[0][3]);
        if(collisions.bottom < bottomCollision) 
            collisions.bottom = bottomCollision;
    }
    return collisions;
}

void World::spellLaunch(Seed* launchedSpell) {
    if(launchedSpell != nullptr) {
        spells.push_back(new Spell(launchedSpell->type, launchedSpell->x, launchedSpell->y, launchedSpell->moveDir, launchedSpell->attached));
    }
}

Mesh* World::getSpellMesh() {
    return spellMesh;
}

Shader* World::getSpellShader() {
    return spellShader;
}