#ifndef Vec_h
#define Vec_h

#include "iostream"

struct vec2 {
    float x, y;
    vec2(float a, float b) {x = a; y = b;}

    vec2 operator - (vec2 v){return vec2(x-v.x, y-v.y);}
    vec2 operator + (vec2 v){return vec2(x+v.x, y+v.y);}
    vec2 operator * (double d){return vec2(x*d, y*d);}
    vec2 operator / (double d){return vec2(x/d, y/d);}
};

struct vec3 {
    float x,y,z;
    vec3(){x=y=z=0;}
    vec3(float a, float b, float c){x=a, y=b, z=c;}

    vec3 operator - (vec3 v){return vec3(x-v.x, y-v.y, z-v.z);}
    vec3 operator + (vec3 v){return vec3(x+v.x, y+v.y, z+v.z);}
    vec3 operator * (double d){return vec3(x*d, y*d, z*d);}
    vec3 operator / (double d){return vec3(x/d, y/d, z/d);}
};

float dot(vec3 vec, vec3 vec1){
    // just the dot product, simple expression below returns its value
    return (vec.x*vec1.x + vec.y*vec1.y + vec.z*vec1.z);
};

float length(vec3 v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
};

vec3 normalize(vec3 v) {
    // calculates the lenght of the vector
    int len = length(v);
    // normalizes the vector by dividing each component by its length and returns it
    return vec3(v.x/len, v.y/len, v.z/len);
};

struct sphere {
    // center point
    vec3 cntr;

    // radius
    float rds;

    // constructor function
    sphere(vec3 a, float r) {
        cntr.x = a.x;
        cntr.y = a.y;
        cntr.z = a.z;
        rds = r;
    }
    // calculates the distance from the given point to the closest point
    // on the surface of the sphere
    float sphereDist(vec3 pos) {
        return length(cntr-pos) - rds;
    }
};

// not in use right now
struct plane {
    vec3 pln;
    plane(vec3 a) {pln = a;}
};

#endif
