#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_thread.h"

#include "Player.hpp"
#include "World.h"

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int x, int y, int width, int height, bool fullscreen);
        void clean();
        void update(double updateRate);
        void render();
        void handleEvents();
        bool running() {return isRunning;}

        std::string parseKey(SDL_Event);

    private:
        int cnt = 0;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext gContext;
        GLint bufferWidth, bufferHeight;
        Player *player;
        GLuint uniformProjection, uniformModel, uniformView;
        glm::mat4 projection;
        World* world;
};

#endif