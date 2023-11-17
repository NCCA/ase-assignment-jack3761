#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"
#include <vector>

class Particle
{
public:
    Vec3 pos;
    Vec3 dir;
    float mass=1.0f;
    Particle() = default;
    void solveConstraints();
    void fixedConstraints();
    void distanceConstraints();
    std::vector<Particle> findNeighbours();
};


#endif