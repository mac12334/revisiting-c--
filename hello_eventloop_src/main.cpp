#include <stdio.h>
#include <SDL2/SDL.h>

const uint FPS = 60;

enum KeyCodes {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

bool keys[] = {false, false, false, false};

void handleKeys(SDL_Event event, bool *input) {
    switch (event.type) {
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w) *(input) = false;
            if (event.key.keysym.sym == SDLK_a) *(input + 2) = false;
            if (event.key.keysym.sym == SDLK_s) *(input + 1) = false;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_w) *(input) = true;
            if (event.key.keysym.sym == SDLK_a) *(input + 2) = true;
            if (event.key.keysym.sym == SDLK_s) *(input + 1) = true;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = true;
            break;
        default:
            break;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("init broke: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("eventloop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool run = true; // same as in pygame
    SDL_Event e; // sdl uses refrences to an event to tell us what the event is
    SDL_Rect rect;
    rect.x = 0; rect.y = 0; rect.w = 50; rect.h = 50;

    uint lastFrame = SDL_GetTicks();

    while (run) { // same as in pygame
        while (SDL_PollEvent(&e) != 0) { // same as for event in pygame.event.get():
            if (e.type == SDL_QUIT) { // same as if event.type == pygame.QUIT:
                run = false; // same as usual
            }

            handleKeys(e, keys);
        }

        if (keys[KEY_UP]) {
            rect.y -= 5;
        }
        if (keys[KEY_LEFT]) {
            rect.x -= 5;
        }
        if (keys[KEY_DOWN]) {
            rect.y += 5;
        }
        if (keys[KEY_RIGHT]) {
            rect.x += 5;
        }

        
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // drawing a white screen and presenting the renderered image
        SDL_RenderClear(render);
        
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderFillRect(render, &rect);
        
        SDL_RenderPresent(render);

        uint currentTime = SDL_GetTicks();
        int delay = (1000 / FPS) - (currentTime - lastFrame);

        if (delay > 0) {
            SDL_Delay(delay);
        }
        lastFrame = SDL_GetTicks();
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}