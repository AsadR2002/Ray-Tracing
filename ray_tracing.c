#include <stdio.h>
#include <SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFFFF

int main() {
    SDL_Init(SDL_INIT_VIDEO); 

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0); 

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect){200, 200, 200, 200};
    SDL_FillRect(surface, &rect, COLOR_WHITE);
    SDL_UpdateWindowSurface(window);

    for (size_t i = 0; i < 50; i++)
    {
        SDL_PumpEvents();
    }

    SDL_Delay(10000);
}