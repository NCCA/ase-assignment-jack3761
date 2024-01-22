#include <iostream>
#include <iomanip>
#include "Particle.h"

Particle::Particle(float _x, float _y, float _z)
{
    m_pos = ngl::Vec3(_x, _y, _z);
    m_p_pos = m_pos;
}

Particle::Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz) : Particle(_x, _y, _z)
{
    m_v = ngl::Vec3(_vx, _vy, _vz);
}


void Particle::draw()
{
    std::cout << std::fixed
              << std::setprecision(2) << (m_pos.m_x <= 0 ? " (" : " ( ")<< m_pos.m_x << "," << (m_pos.m_y <= 0 ? "" : " ") << m_pos.m_y << "," << (m_pos.m_z <= 0 ? "" : " ") << m_pos.m_z << ")\n";
}

void Particle::p_draw()
{
    std::cout << std::fixed
        << std::setprecision(2) << (m_p_pos.m_x <= 0 ? " (" : " ( ") << m_p_pos.m_x << "," << (m_p_pos.m_y <= 0 ? "" : " ") << m_p_pos.m_y << "," << (m_p_pos.m_z <= 0 ? "" : " ") << m_p_pos.m_z << ")\n";
}

float Particle::getMass() const
{
	return m_mass;
}

float Particle::getInvMass() const
{
	return 1.0f / m_mass;
}


