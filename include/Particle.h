#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include <vector>

class Particle
{
public:
    ngl::Vec3 pos;
    ngl::Vec3 dir;
    float mass=1.0f;
    Particle() = default;
    Particle(float _x, float _y, float _z);
    Particle(float _x, float _y, float _z, float _xdir, float _ydir, float _zdir);
    void solveConstraints();
    void fixedConstraints();
    void distanceConstraints();
    std::vector<Particle> findNeighbours();
};


#endif