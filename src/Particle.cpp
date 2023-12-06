#include <iostream>
#include <iomanip>
#include "Particle.h"

Particle::Particle(float _x, float _y, float _z)
{
    pos = ngl::Vec3(_x, _y, _z);
    p_pos = pos;
}

Particle::Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz) : Particle(_x, _y, _z)
{
    v = ngl::Vec3(_vx, _vy, _vz);
}

void Particle::applyForces(float _gravity, ngl::Vec3 _wind, size_t _timeStep)
{
    v += ngl::Vec3{0, _gravity, 0} * _timeStep + _wind * _timeStep;
    p_pos += v * _timeStep;
}

void Particle::applyFixedConstraint()
{
    ngl::Vec3 dt = pos - p_pos;
    p_pos += dt;
}

void Particle::draw()
{
    std::cout << std::fixed
              << std::setprecision(2) << (pos.m_x <= 0 ? " (" : " ( ")<< pos.m_x << "," << (pos.m_y <= 0 ? "" : " ") << pos.m_y << "," << (pos.m_z <= 0 ? "" : " ") << pos.m_z << ")\n";

}



