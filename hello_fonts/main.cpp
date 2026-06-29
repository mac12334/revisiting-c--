#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("something went wrong: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) { // the error code for ttf is -1
        printf("something wrong: %s\n", TTF_GetError());
        return 2;
    }
    
    SDL_Window* window = SDL_CreateWindow("hello fonts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("hello_fonts/PlayfulTime-BLBB8.ttf", 32); // similar to pygame Font object
    // note- for now only use TTF_RenderText_Solid because the other two described in that one tutorial did not work and the only one that did was this function
    SDL_Surface* surf = TTF_RenderText_Solid(font, "Test", SDL_Color{255, 255, 255}); // very similar to "font.render(text, anti-alliase, etc)" but does not require anti-aliase condition

    SDL_Rect r{50, 100, surf->w, surf->h}; // -> is like object.item(python) or object::item(c++)
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surf);

    SDL_FreeSurface(surf);

    bool run = true;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) run = false;
        }

        SDL_RenderClear(render);

        SDL_RenderCopy(render, tex, NULL, &r);

        SDL_RenderPresent(render);
    }
    TTF_CloseFont(font); // you need to free the font from memory
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit(); // always pair up initializations to quiting
    SDL_Quit();

    return 0;
}