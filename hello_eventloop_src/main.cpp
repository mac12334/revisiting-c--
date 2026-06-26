#include <stdio.h>
#include <SDL2/SDL.h>

const uint FPS = 60;

// SDL does have keycode inputs, not like pygame though
// I used a trick I saw someone online use to make it more like pygame and make it easier to understand for me.

enum KeyCodes { // kind of like pygame constants that are used for indexing pygames key input list.
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

bool keys[] = {false, false, false, false}; // this is the list that is updated everytime a key is pressed and unpressed

void handleKeys(SDL_Event event, bool *input) { // A function to abstract the process of checking which indexes should be fired on or off
    switch (event.type) {
        case SDL_KEYUP: // when you stop pressing the button
            // *(input) is the adress for the first index of 'input' and setting that index to false in the action that key is the current key event
            // *(input + N) is the syntax for using pointers to index an array
            if (event.key.keysym.sym == SDLK_w) *(input) = false;
            if (event.key.keysym.sym == SDLK_a) *(input + 2) = false;
            if (event.key.keysym.sym == SDLK_s) *(input + 1) = false;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = false;
            break;
        case SDL_KEYDOWN: // when you press the button
            // Same principle but instead of setting the index to false it makes it true saying 'this button is being held down'.
            if (event.key.keysym.sym == SDLK_w) *(input) = true;
            if (event.key.keysym.sym == SDLK_a) *(input + 2) = true;
            if (event.key.keysym.sym == SDLK_s) *(input + 1) = true;
            if (event.key.keysym.sym == SDLK_d) *(input + 3) = true;
            break;
        default: // nothing happens
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
    rect.x = 0; rect.y = 0; rect.w = 50; rect.h = 50; // in SDL rectangles are structs instead of objects like in pygame

    uint lastFrame = SDL_GetTicks();

    while (run) { // same as in pygame
        while (SDL_PollEvent(&e) != 0) { // same as for event in pygame.event.get():
            if (e.type == SDL_QUIT) { // same as if event.type == pygame.QUIT:
                run = false; // same as usual
            }

            handleKeys(e, keys); // in the definition of this function the second input was a pointer to a boolean value
            // but we passeed in an array, that is because you can write an array as the refrence to the first index
            // indexing the array just means you have to add to the current adress by some amount depending on the type of object.
        }

        if (keys[KEY_UP]) { // same as using pygame but using personal abstractions instead of hand crafted ones
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
        
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255); // drawing onto a white screen a black rectangle to show user inputs
        SDL_RenderFillRect(render, &rect);
        
        SDL_RenderPresent(render);

        uint currentTime = SDL_GetTicks(); // delay math
        int delay = (1000 / FPS) - (currentTime - lastFrame); // the delay has to be an integer so that it doesn't underflow when trying to be negative.
        // if the delay underflows (when the amount of time elapsed is greater than the time needed to keep a steady FPS) the delay will then be unbearably long.

        if (delay > 0) { // If you delay with a negative number than that might result in an error
            SDL_Delay(delay);
        }
        lastFrame = SDL_GetTicks(); // update the last frame time to now so that the delay math works.
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}