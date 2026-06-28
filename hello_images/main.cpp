#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // for images you need to use a different library that when installed is put into the SDL folder

enum KeyIndexes {
    K_w,
    K_a,
    K_s,
    K_d
};

bool keyInputs[4];

void handleKeyInput(SDL_Event event, bool *input) {
    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_w) *(input) = true;
            if (event.key.keysym.sym == SDLK_a) *(input + 1) = true;
            if (event.key.keysym.sym == SDLK_s) *(input + 2) = true;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = true;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w) *(input) = false;
            if (event.key.keysym.sym == SDLK_a) *(input + 1) = false;
            if (event.key.keysym.sym == SDLK_s) *(input + 2) = false;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = false;
            break;
        default:
            break;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("don't work: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) { // similar to initializing SDL, in pygame it's just included in the package
        printf("dont work: %s\n", IMG_GetError());
        return 2;
    }

    SDL_Window* window = SDL_CreateWindow("hello images", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // render accelerated is using the GPU to speed up the proccess

    SDL_Surface* car = IMG_Load("hello_images/racecar-genre2-concept-character2.png"); // you need to load the image into an SDL usuable format (surface) like in pygame
    SDL_Texture* carTex = SDL_CreateTextureFromSurface(render, car); // since we are using render accelerated we need to provide a texture to supply the GPU

    bool run = true;
    SDL_Event e;

    SDL_Rect r = {10, 10, 100, 100}; // a different way to initialize a rect like in pygame: pygame.Rect(0, 0, 50, 50)

    SDL_FreeSurface(car); // since c++ is a memory language you need to free every surface from the heap
    uint lastFrame = SDL_GetTicks();

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
            handleKeyInput(e, keyInputs);
        }

        if (keyInputs[K_w]) r.y -= 5; // more effiecient in space to do it like this
        if (keyInputs[K_a]) r.x -= 5;
        if (keyInputs[K_s]) r.y += 5;
        if (keyInputs[K_d]) r.x += 5;

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        SDL_RenderCopy(render, carTex, NULL, &r);// renders a copy of a texture on the surfac: win.blit(surf, des) # in pygame

        SDL_RenderPresent(render);

        uint currentTime = SDL_GetTicks();
        int delay = (1000 / 60) - (currentTime - lastFrame);

        if (delay > 0) {
            SDL_Delay(delay);
        }
        lastFrame = SDL_GetTicks();
    }

    SDL_DestroyTexture(carTex); // you have to destroy the texture like freeing a surface
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit(); // you have to de-initialize all of image to finish the program.
    SDL_Quit();

    return 0;
}