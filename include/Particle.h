#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include <vector>

class Particle
{
public:
    ngl::Vec3 pos; // actual position
    ngl::Vec3 p_pos; // proposed position
    ngl::Vec3 v; // velocity
    std::vector<Particle*> neighbours; // neighbouring particles
    bool isFixed=false;
    float mass=1.0f;
    Particle() = default;
    Particle(float _x, float _y, float _z);
    Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz);
    void applyForces(float _gravity, ngl::Vec3 _wind, size_t _timeStep);
    void solveConstraints();
    void applyFixedConstraint();
    void distanceConstraints();
    void draw();
};


#endif