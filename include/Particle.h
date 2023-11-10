#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"

struct Particle
{
    Particle() = default;
    Vec3 pos;
    Vec3 dir;
    float mass=1.0f;
};


#endif