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
    ngl::Vec3 a; // accumulator
    std::vector<Particle*> neighbours; // neighbouring particles
    bool isFixed=false;
    float mass=0.1f;
    Particle() = default;
    Particle(float _x, float _y, float _z);
    Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz);
    void draw();
    void p_draw();
    float getMass() const;
    float getInvMass() const;

};


#endif