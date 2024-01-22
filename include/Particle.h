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
	ngl::Vec3 m_pos; // actual position
	ngl::Vec3 m_p_pos; // proposed position
	ngl::Vec3 colour = { 0,0,0 }; // colour
	ngl::Vec3 m_v; // velocity
	std::vector<Particle*> m_neighbours; // neighbouring m_particles
	std::vector<bool> m_yNeighbours; // neighbouring m_particles relationship
	float m_mass;
	bool isFixed=false;	
	void draw();
	void p_draw();
	float getMass() const;
	float getInvMass() const;

};


#endif
