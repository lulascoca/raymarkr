#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "raymarcher.h"
#include "vec.h"

#define WIDTH 1028
#define HEIGHT 720

#define MAX_STEPS 400
#define MAX_DIST 400
#define SURF_DIST 0.01

using namespace std;

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

void render(vec2 fragCoord, vec2 iResolution, SDL_Window *window, SDL_Renderer *renderer) {
    vec2 uv = vec2(fragCoord.x/iResolution.x, fragCoord.y/iResolution.y);
    cout << uv.x << endl;
    camera cameravis = camera(vec3(0.0, 1.0, 0.0), normalize(vec3(uv.x, uv.y, 1)));

    cameravis.rd = vec3(uv.x, uv.y, 1.0)/length(vec3(uv.x, uv.y, 1.0));

    // distance to the intersection
    int d = RayMarch(cameravis.ro, cameravis.rd, MAX_STEPS, MAX_DIST, SURF_DIST);
    d = d/200;
    d = clip(d, 0, 255);

    vec3 surfPoint = cameravis.ro + cameravis.rd*d;
    
    vec3 col = vec3(d, d, d);
    SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
    SDL_RenderDrawPoint(renderer, uv.x, uv.y);
}

int main(){    
    // declaration of the future renderer and window
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    // initializes graphics and shit
    SDL_Init(SDL_INIT_EVERYTHING);
    cout << "initialized all things" << endl;

    // creantes windows and renderers using pointers to the names specified before
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    // sets the drawcolor to black
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // clears the screen with the color defined in the line above
    SDL_RenderClear(renderer);

    // vec2 that stores x and y of screen
    vec2 iResolution = vec2(WIDTH, HEIGHT);
    // vec2 that is gonna store te current pixel being written to
    vec2 fragCoord = vec2(0, 0);

    // confusing af but it works(idk) :)
    while (true){
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        while (fragCoord.x <= iResolution.x) {
            while (fragCoord.y <= iResolution.y) {
                // loop over function just like in shader toy with the fragcoord being
                // given every time
                render(fragCoord, iResolution, window, renderer);
                
                ++fragCoord.y;
            }
            fragCoord.y = 0;
            ++fragCoord.x;
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(1000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}