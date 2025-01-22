#include <stdio.h>
#include <SDL.h>
#include <math.h>

const int RAYS_NUMBER = 100;
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
        double angle = ((double)i / RAYS_NUMBER) * 360.0;
    }
}

