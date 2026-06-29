#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL did not init: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("image did not init: %s\n", IMG_GetError());
        return 2;
    }

    SDL_Window* win = SDL_CreateWindow("hello animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surf = IMG_Load("hello_animation/racecar-genre2-both-animations.png");
    if (surf == NULL) {
        printf("image did not load: %s\n", IMG_GetError());
        return 3;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);

    int width = surf->w/4; // A sample rectangle uses the full size of the texture so to get a cell you need to divide the size by the rows and columns
    int height = surf->h/2;

    SDL_Rect sample = {0,0,width,height}; // This is just the destination of the first cell ontop
    SDL_Rect pos = {50, 50, 100, 100}; // location where the cell will be drawn and the size it should be drawn x: 50, y: 50, width: 100, height: 100

    uint xIndex = 0; // index of the cell of animation
    uint yIndex = 0; // index of the action being animation 0: drive forward, 1: turn right
    uint lastUpdate = SDL_GetTicks(); // similar to forcing the game FPS but is used to force the animation FPS

    SDL_FreeSurface(surf);

    SDL_Event e;
    bool run = true;

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) run = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d) yIndex = 1; // got lazy and didn't want to make the key input system I would usually make
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_d) yIndex = 0;
        }

        uint currentTime = SDL_GetTicks();
        if (currentTime - lastUpdate >= 100) { // very similar to processes in pygame, just different syntax
            xIndex++;
            lastUpdate = currentTime;
        }
        if (xIndex >= 4) xIndex = 0; // ensure that the index is in [0, 1, 2, 3]
        sample.x = width*xIndex; // You can use the width as the unit of movement and the index as the amount of units to move
        sample.y = height*yIndex; // same for y

        SDL_SetRenderDrawColor(rend, 200, 200, 200, 255); // the colors used in the animation can blend into a white background
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, tex, &sample, &pos); // use both the sample and the destination rects to draw the correct cell at the correct place.

        SDL_RenderPresent(rend);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}