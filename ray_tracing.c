#include <stdio.h>
#include <SDL.h>
#include <math.h>


#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFFFF
#define BLACK 0x00000000
#define RAY_COLOR 0xffd43b
#define RAY_THICKNESS 1

const int RAYS_NUMBER = 1000;

struct Circle 
{
    int x;
    int y;
    int r;
};

struct Ray {
    double start_x, start_y; 
    double ang; 
    double end_x, end_y;    
};

void create_rays(struct Circle circle, struct Ray rays[])
{
    
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }
}

void ray_fill(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object)
{
    double sqrd_rad = pow(object.r, 2);
    for(int i=0;i < RAYS_NUMBER; i++) {
        struct Ray ray = rays[i];

        int end_of_screen = 0; 
        int object_hit = 0;

        double step = 1;
        double x_draw = ray.start_x;
        double y_draw = ray.start_y;

        while(!end_of_screen && !object_hit) {
            x_draw += step*cos(ray.ang);
            y_draw += step*sin(ray.ang); 

            SDL_Rect ray_point = (SDL_Rect) {x_draw, y_draw, RAY_THICKNESS, RAY_THICKNESS};
            SDL_FillRect(surface, &ray_point, color);

            if (x_draw < 0 || x_draw > WIDTH) end_of_screen = 1;
            if (y_draw < 0 || y_draw > HEIGHT) end_of_screen = 1;

            double sqrd_distance = pow(x_draw-object.x, 2) + pow(y_draw-object.y, 2);
            if (sqrd_distance < sqrd_rad) {
                object_hit = 1;
            }
        }
    }
}

void circle_fill(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    double sqrd_rad = pow(circle.r, 2);
    for (double x=circle.x-circle.r; x<=circle.x+circle.r;x++) {
        for (double y= circle.y-circle.r; y<=circle.y+circle.r ;y++) {
            double sqrd_distance = pow(x-circle.x, 2) + pow(y-circle.y, 2);
            if (sqrd_distance < sqrd_rad) {
                SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO); 

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0); 

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200, 200, 40};
    struct Circle object = {400, 300, 100};
    SDL_Rect erase = {0, 0, WIDTH, HEIGHT};

    struct Ray rays[RAYS_NUMBER]; 
    create_rays(circle, rays);

    double object_speed = 2; 
    double object_speed_x = 4;
    int sim_run = 1;
    SDL_Event event;
    while (sim_run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                sim_run = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                create_rays(circle, rays);
            }
        }
        SDL_FillRect(surface, &erase, BLACK);
        ray_fill(surface, rays, RAY_COLOR, object);
        circle_fill(surface, circle, COLOR_WHITE);
        
        circle_fill(surface, object, COLOR_WHITE);  

        object.y += object_speed;
        if (object.y + object.r > HEIGHT || object.y - object.r < 0) object_speed = -object_speed;

        object.x += object_speed_x;
        if (object.x + object.r > WIDTH || object.x - object.r < 0) object_speed_x = -object_speed_x;

        
          
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    //for (size_t i = 0; i < 50; i++)
   // {
    //    SDL_PumpEvents();
   // }
}