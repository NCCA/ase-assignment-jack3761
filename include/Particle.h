#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include <vector>

class Particle
{
public:
	Particle() = default;
	Particle(float _x, float _y, float _z);
	Particle(float _x, float _y, float _z, float _vx, float _vy, float _vz);
	ngl::Vec3 pos; // actual position
	ngl::Vec3 p_pos; // proposed position
	ngl::Vec3 v; // velocity
	std::vector<Particle*> neighbours; // neighbouring particles
	std::vector<bool> yNeighbours; // neighbouring particles relationship
	bool isFixed=false;
	float mass;
	void draw();
	void p_draw();
	float getMass() const;
	float getInvMass() const;

};


#endif
