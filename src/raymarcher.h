#ifndef Raymarcher_H
#define Raymarcher_H

#include <SDL2/SDL.h>
#include <algorithm>
#include "vec.h"

struct camera {
    vec3 ro;
    vec3 rd;
    camera(vec3 ro_, vec3 rd_) {
        ro = ro_;
        rd = rd_;
    }
};

float getDist(vec3 p) {
    // x is left to right
    // y is down to up
    // z is camera to front
    // r is the radius of the sphere
    //                      x    y    z     r
	sphere s = sphere(vec3(0.0, 1.0, 2.0), 1.0);
    
    // calculates the lentgh of the vector from the camera to the center of
    // the sphere and subtracts the radius to assure we dont go into it oof
    // s.w is the radius apparently
    float sphereDist = s.sphereDist(p);
    
    // distance to the plane that is right below the camera so we just use y coord
    float planeDist = p.y;
    
    // overall distance is the minimum of both distances
    float overallDist = std::min(sphereDist, planeDist);
    return sphereDist;
}

float RayMarch(vec3 ro, vec3 rd, int max_steps, float max_dist, float surf_dist){
    // distance to the origin is 0 If there is an interception right away
    float distOrig = 0.0;
    
    for(int i=0; i < max_steps; i++) {
        // calculates a safe position taht wont go into any objects
        // by adding the raydirection times the current distance calculated
        // to the rayorigin 
    	vec3 curPos = ro + rd*distOrig;

        //  
        float dS = getDist(curPos);
        distOrig += dS;
        // if the distance of the sphere at the point is smaller than the surf dist
        // or if its bigger than the biggest possible distance then break the loop and return the distance
        if(distOrig > max_dist || dS < surf_dist) break;
    }

    return distOrig;
}


#endif