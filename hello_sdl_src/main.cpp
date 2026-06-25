#include <stdio.h>
#include <SDL2/SDL.h>

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // kinda like pygame.init()
        printf("SDL init blocked: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0); // same as win = pygame.display.set_mode()
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // renderer is used as a drawing tool

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // sets the draw color to white
    SDL_RenderClear(render); // fills the screen with the draw color
    SDL_RenderPresent(render); // displays the screen
    // same as win.fill((255, 255, 255))
    // pygame.display.update() | pygame.display.flip()

    SDL_Delay(2000); // same as a wait command, pretty standard

    SDL_DestroyRenderer(render); // since c/c++ is memory based you have to free up the complicated data
    SDL_DestroyWindow(window);
    SDL_Quit(); // same as pygame.quit()

    return 0;
}