#include <iostream>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>

#include "mathstuff.hpp"
#include "types.hpp"
#include "shapes.hpp"
#include "ray.hpp"

#define WIDTH 800.0f
#define HEIGHT 600.0f

#define PI 3.141592653f
#define XFOV (120.0f/180.0f*PI)
#define YFOV (90.0f/180.0f*PI)

void plot(SDL_Renderer* renderer, float x, float y, Color c) {
    SDL_SetRenderDrawColor(renderer, (int)c.x*255, (int)c.y*255, (int)c.z*255, 255);
    SDL_RenderDrawPoint(renderer, (int)x, (int)y);
}

int main() {
    // yaw pitch
    Camera camera{Vector{0, 0, 0}, 0, 0};
    Sphere sphere1(Vector{0, 0, 100}, 30);
    Sphere sphere2(Vector{50, 0, 100}, 10);
    Object object1{sphere1, Material{Vector{1, 0.3, 0.3}}};
    Object object2{sphere2, Material{Vector{0.3, 1, 0.3}}};
    std::vector<Object> objects;
    objects.push_back(object1);
    objects.push_back(object2);
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::srand(time(nullptr));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer((int)WIDTH, (int)HEIGHT, 0,
        &window, &renderer);
    SDL_SetWindowTitle(window, "The Rays Go Marching One by One");
    
    while (1) {
        // input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                goto exit;
            }
            //
        }
        // update
        // render
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        // for every pixel
        for (float dxp = 0; dxp < WIDTH; dxp++) {
            for (float dyp = 0; dyp < HEIGHT; dyp++) {
                float yaw_offset = map(dxp, 0, WIDTH, -XFOV/2, XFOV/2);
                float pitch_offset = map(dyp, 0, HEIGHT, -YFOV/2, YFOV/2);
                float pitch = camera.pitch + pitch_offset;
                float yaw = camera.yaw + yaw_offset;
                Vector direction{
                    std::sin(yaw),
                    std::sin(pitch),
                    std::cos(yaw),
                };
                if (ray_march(camera.position, direction, objects).hit) {
                    plot(renderer, dxp, dyp, Color{1, 0, 0});
                }
            }
        }
        SDL_RenderPresent(renderer);
        std::cout << "Hello, World" << std::endl;
    }
exit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}