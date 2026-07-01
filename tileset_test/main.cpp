#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Pos { // just an abstraction to make returning (x, y) easy
    int x, y;
};

Pos getMapPostion(int index, int numCol) { // returns the texture map X and Y position based on an index and the number of columns
    int x = index % numCol; // this math was prototyped in the python file to get an idea of what logic was needed for this operation
    int y = index / numCol;
    return Pos {x, y};
}

void drawMap(SDL_Renderer* renderer, SDL_Texture* texture, int tTileSide, int rTileSide, int (*map)[12]) { // draws the map
    for (int y = 0; y < 12; y++) { // loops through the rows
        for (int x = 0; x < 12; x++) { // loops through the columns
            int index = map[y][x]; // gets what item is needed to be drawn
            if (index == -1) continue; // common way to not have to draw a tile
            Pos mapPos = getMapPostion(index, 4);
            SDL_Rect texRect = {mapPos.x * tTileSide, mapPos.y * tTileSide, tTileSide, tTileSide}; // same as with animations you need the sample rect and the destination rect
            SDL_Rect realRect = {rTileSide * x, rTileSide * y, rTileSide, rTileSide};
            SDL_RenderCopy(renderer, texture, &texRect, &realRect); // draws the tile at the specified location
        }
    }
}


int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL init didn't: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("image init didn't: %s\n", IMG_GetError());
        return 2;
    }

    int map[12][12] = { // A map of what tiles need to go where
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  2, -1},
        {-1,  4,  5,  5,  5,  5,  5,  5,  5,  5,  6, -1},
        {-1,  4,  5,  5,  5,  5,  5,  5,  5,  5,  6, -1},
        {-1,  4,  5,  5,  5,  5,  5,  5,  5,  5,  6, -1},
        {-1,  4,  5,  5,  5,  5,  5,  5,  5, 12, 10, -1},
        {-1,  4,  5,  5,  5,  5,  5,  5, 12, 10, -1, -1},
        {-1,  8,  9,  9,  9,  9,  9,  9, 10, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1}
    };

    SDL_Window* win = SDL_CreateWindow("test tileset", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surfMap = IMG_Load("tileset_test/texture-map.png");
    SDL_SetColorKey(surfMap, SDL_RLEACCEL, SDL_MapRGBA(surfMap->format, 255, 255, 255, 0)); // only learned this, this time. You need to ensure you color key the transparant pixels if you want to use a semi-transparant image

    int tileWidth = surfMap->w / 4;
    int tileHeight = surfMap->h / 5;

    SDL_Texture* texMap = SDL_CreateTextureFromSurface(rend, surfMap);

    SDL_Rect pos = {200, 100, 50, 50}; // because I added a simple spritesheet to the texture map I wanted to see how well it animated while mapping
    SDL_Rect anim = {tileWidth * 3, 0, tileWidth, tileHeight}; // the position of the first animation cell

    SDL_FreeSurface(surfMap);

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texMap, SDL_BLENDMODE_BLEND);

    bool run = true;
    SDL_Event e;

    uint lastFrame = SDL_GetTicks();

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) run = false;
        }

        uint currentTime = SDL_GetTicks();
        if (currentTime - lastFrame >= 200) {
            anim.y += tileHeight;
            anim.y %= tileHeight * 3;
            lastFrame = currentTime;
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderClear(rend);

        drawMap(rend, texMap, tileWidth, 50, map); // calls the function to draw the map onto the screen
        SDL_RenderCopy(rend, texMap, &anim, &pos); // draws the current frame of animation from the texture map as well

        SDL_RenderPresent(rend);
    }

    SDL_DestroyTexture(texMap);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}