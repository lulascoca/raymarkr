#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "raymarcher.h"
#include "vec.h"

#define WIDTH 600
#define HEIGHT 400

#define MAX_STEPS 400
#define MAX_DIST 400
#define SURF_DIST 0.01

using namespace std;

void putpixel();

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

int render(vec2 iResolution, SDL_Window *window, SDL_Renderer *renderer) {
    vec2 tfragCoord = vec2(iResolution.x, iResolution.y);
    vec2 fragCoord = (tfragCoord - iResolution*0.5)/iResolution.y;
    //cout << fragCoord.x << " " << fragCoord.y << endl;
    //SDL_Delay(1000);
    camera cameravis = camera(vec3(0, 1, 0), normalize(vec3(int(fragCoord.x), int(fragCoord.y), 1)));
    
    // confusing af but it works(idk) :)
    while(fragCoord.x < iResolution.x) {
        while (fragCoord.y <= iResolution.y) {
            cameravis.rd = vec3(fragCoord.x, fragCoord.y, 1);
            //SDL_Delay(100);
            cout << cameravis.rd.x << " " << cameravis.rd.y << " " << cameravis.rd.z << endl;
            // get distance with raymarching calculation
            int d = RayMarch(cameravis.ro, cameravis.rd, MAX_STEPS, MAX_DIST, SURF_DIST);
            d = d/200;
            d = clip(d, 0, 255);
            cout << d << endl;
            vec3 surfPoint = cameravis.ro + cameravis.rd*d;
            
            vec3 col = vec3(d, d, d);
            SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
            SDL_RenderDrawPoint(renderer, fragCoord.x, fragCoord.y);
            ++fragCoord.y;
        }
        SDL_RenderPresent(renderer);
        fragCoord.y = 0;
        ++fragCoord.x;
    }

    // Get the next event
    SDL_Event event;
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT)
        {
            return 0;
        }
    }
    
    return 1;
}

int main(){    
    // declaration of the future renderer and window
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *screen;
    screen = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888);

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

    // present the render
    int i = 0;
    render(iResolution, window, renderer);
    SDL_Delay(5000);
    ++i;


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}