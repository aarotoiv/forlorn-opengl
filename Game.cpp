#include "Game.hpp"

Game::Game() {
}
Game::~Game() {

}
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    flags = SDL_WINDOW_OPENGL;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        
        //MULTISAMPLING GAY
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

        
        std::cout << "SUBSYSTEMS INITIALIZEd" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "window created" << std::endl;
        }
        /*renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            std::cout << "Renderer created" << std::endl;
        }*/
        

        gContext = SDL_GL_CreateContext(window);
        if(gContext == NULL) {
            printf("FAILED TO CREATE OGL CONTEXT");
            clean();
            return;
        } else {
            //initialize glew
            glewExperimental = true;
            GLenum glewError = glewInit();
            if(glewError != GLEW_OK) {
                printf("FAILED TO INIT GLEW");
                clean();
                return;
            }

            //use vsync???
            /*if(SDL_GL_SetSwapInterval(1) < 0) {
                printf("UNABLE TO SET VSYNC");
            }*/

            //glEnable(GL_DEPTH_TEST);

            SDL_GL_GetDrawableSize(window, &bufferWidth, &bufferHeight);

            glViewport(0,0,bufferWidth, bufferHeight);

            glDisable(GL_CULL_FACE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_MULTISAMPLE);

            

            //INITIALIZE player
            projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
            player = new Player();
            world = new World();
            
        }
        isRunning = true;
    } 
}

void Game::update(double updateRate) {
    //UPDATE FUNCTION
    player->Update(updateRate);
    Collisions collisions = world->checkCollisions(player->GetX(), player->GetBottom(), player->GetWidth(), player->GetHeight());
    //std::cout << collisions.bottom << std::endl;
    player->HandleCollisions(collisions.bottom, collisions.left, collisions.top, collisions.right);
}

void Game::render() {
    //projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //RENDER FUNCTION
    //HANDLE THE MATRICES IN player?
    player->Draw(projection);
    world->draw(projection, player->GetX(), player->YPosForDraw());
    SDL_GL_SwapWindow(window);
    //SDL_RenderPresent(renderer);
}
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_KEYDOWN:
            player->HandleKeyDown(parseKey(event));
            break;
        case SDL_KEYUP:
            player->HandleKeyUp(parseKey(event));
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

std::string Game::parseKey(SDL_Event event) {
    switch(event.key.keysym.sym) {
        case SDLK_a: 
            return "left";
            break;
        case SDLK_d:
            return "right";
            break;
        case SDLK_SPACE:
            return "space";
            break;
        default: 
            return "";
            break;
    }
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(gContext);
    SDL_Quit();
    std::cout << "GAME CLEANED" << std::endl;
}
