#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include <vector>

class Particle
{
public:
    ngl::Vec3 pos;
    ngl::Vec3 p_pos;
    ngl::Vec3 v;
    float mass=1.0f;
    Particle() = default;
    Particle(float _x, float _y, float _z);
    Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz);
    void applyForces(float _gravity, ngl::Vec3 _wind, size_t _timeStep);
    void solveConstraints();
    void fixedConstraints();
    void distanceConstraints();
    std::vector<Particle> findNeighbours();
};


#endif