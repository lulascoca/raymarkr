// this is the code from the art of code youtuber lmao I dont understand shit
#include "vec.h"

#define MAX_STEPS 200
#define MAX_DIST 1000.0
#define SURF_DIST 0.000000000

float getDist(vec3 p){
    // x is left to right
    // y is down to up
    // z is camera to front
    // r is the radius of the sphere
    // wtf
    //             x    y    z    r
	vec4 s = vec4(0.0, 1.0, 6.0, 1.0);
    
    // calculates the lentgh of the vector from the camera to the center of
    // the sphere and subtracts the radius to assure we dont go into it oof
    // s.w is the radius apparently
    float sphereDist = length(p-s.xyz) - s.w;
    
    // distance to the plane that is right below the camera so we just use y coord
    float planeDist = p.y;
    
    // overall distance is the minimum of both distances
    float overallDist = min(sphereDist, planeDist);
    
    return overallDist;
}

float RayMarch(vec3 ro, vec3 rd){
	float dO = 0.0;
    
    for(int i=0; i<MAX_STEPS; i++) {
    	vec3 p = ro + rd*dO;
        float dS = getDist(p);
        dO += dS;
        // if the distance of the sphere at the point is smaller than the surf dist
        // or if its bigger than the biggest possible distance then break the loop and return the distance
        if(dO>MAX_DIST || dS<SURF_DIST) break;
    }
    
    return dO;
}

vec3 getNormal(vec3 surfPos){
	float d = getDist(surfPos);
    vec2 e = vec2(0.01, 0);
        
    vec3 n = d - vec3(
        getDist(surfPos-e.xyy),
        getDist(surfPos-e.yxy),
        getDist(surfPos-e.yyx));
    
    return normalize(n);
}

float getLight(vec3 surfPos){
	vec3 lightPos = vec3 (0, 5, 6);
    lightPos.xz += vec2(sin(iTime), cos(iTime));
    vec3 lightDir = normalize(lightPos-surfPos);
    
    vec3 n = getNormal(surfPos);
    
    // since the dot product returns from -1.0 to 1.0 we have to limit the results
    // to 0.0 to 1.0
    float dif = clamp(dot(n, lightDir), 0.0, 1.0);
    
    // in this raymarch function the ray origin is the surface position
    // plus the normal vector times a small number because if we pass a point in a surface
    // it just returns right away since there is an intersection
    float d = RayMarch(surfPos+n*0.2, lightDir);
    // checks if the distance raymarched is smaller than the actual distance to the light
    // if it is its because there is an object in front of the light so there must be shadow in that point
    if(d<length(lightPos-surfPos)) dif = dif*0.1;
    
    // returns the difusion
    return dif;

}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1) and place the 0,0 at the center of the screen
    vec2 uv = (fragCoord - 0.5*iResolution.xy)/iResolution.y;
    
    // ray origin and ray directions so basically camera
    vec3 ro = vec3(0.0, 1.0, 0.0);
    // the direction of the rays pretty much
    vec3 rd = normalize(vec3(uv.x, uv.y, 1.0));
    
    // the actual raymarching thingy that takes in the ray origin and direction
    float d = RayMarch(ro, rd);
    
    // calculates the surface position by adding the raydirection times the distance to the ray origin
    vec3 p = ro + rd*d;
    
    float dif = getLight(p);
    
    vec3 col = vec3(dif);
    // col = getNormal(p);
    
    // output to the screen
    fragColor = vec4(col, 1.0);
}
