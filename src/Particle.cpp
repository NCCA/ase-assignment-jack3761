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


void Particle::draw()
{
    std::cout << std::fixed
              << std::setprecision(2) << (pos.m_x <= 0 ? " (" : " ( ")<< pos.m_x << "," << (pos.m_y <= 0 ? "" : " ") << pos.m_y << "," << (pos.m_z <= 0 ? "" : " ") << pos.m_z << ")\n";
}

void Particle::p_draw()
{
    std::cout << std::fixed
        << std::setprecision(2) << (p_pos.m_x <= 0 ? " (" : " ( ") << p_pos.m_x << "," << (p_pos.m_y <= 0 ? "" : " ") << p_pos.m_y << "," << (p_pos.m_z <= 0 ? "" : " ") << p_pos.m_z << ")\n";
}

float Particle::getMass() const
{
	return mass;
}

float Particle::getInvMass() const
{
	return 1.0f / mass;
}


