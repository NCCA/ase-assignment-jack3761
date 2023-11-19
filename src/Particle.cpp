#include "Particle.h"

Particle::Particle(float _x, float _y, float _z)
{
    pos = ngl::Vec3(_x, _y, _z);
}

Particle::Particle(float _x, float _y, float _z, float _xdir, float _ydir, float _zdir) : Particle(_x, _y, _z)
{
    dir = ngl::Vec3(_xdir, _ydir, _zdir);
}



