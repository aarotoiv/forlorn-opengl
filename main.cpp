#include "Game.hpp"

const int FPS = 120;
const int frameDelay = 1000/FPS;
Game *game = nullptr;
SDL_Thread *update = nullptr;
SDL_Thread *render = nullptr;
SDL_Thread *event = nullptr;
std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());

int updateThread(void *data);
int renderThread(void *data);
int eventThread(void *data);


int main(int argc, char* args[]) {

    game = new Game();

    game->init("Meme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, false);

    Uint32 frameStart;
    int frameTime;

    update = SDL_CreateThread(updateThread, "updating", NULL);
    event = SDL_CreateThread(eventThread, "events", NULL);

    while(game->running()) {
        frameStart = SDL_GetTicks();
        
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay-frameTime);
        }
    }

    game->clean();
    
    return 0;
}
int updateThread(void *data) {
    while(game->running()) {
        std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) - ns;
        double updateRate = ((double)diff.count() / (double)1000000000);
        if(updateRate >= (double)1.0/(double)FPS) {
            game->update(updateRate);
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
        }
    }
}

int eventThread(void *data) {
    while(game->running()) {
        game->handleEvents();
    }
}
