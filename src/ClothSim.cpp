#include "ClothSim.h"

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _simDuration) : gravity{_gravity}, wind{_wind}, timeStep{_timeStep}, solveIterations{_simDuration}
{}

ClothSim::ClothSim(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight)
{
    mesh = ClothMesh(_cWidth, _cHeight, _pWidth, _pHeight);
}

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _simDuration, float _cWidth,
                   float _cHeight, size_t _pWidth, size_t _pHeight) : ClothSim(_gravity, _wind, _timeStep, _simDuration)
{
    mesh = ClothMesh(_cWidth, _cHeight, _pWidth, _pHeight);
}

void ClothSim::runSim()
{
        // initialise sim
        for (size_t i=0; i<mesh.getParticleWidth(); ++i)
        {
            for (size_t j = 0; j < mesh.getParticleHeight(); ++j)
            {
                mesh.findNeighbours(i,j);
                mesh.getParticle(i,j).applyForces(gravity, wind, timeStep);
            }
        }

        // apply constraints for each particle with particle centric approach
        // solve distance constraints
        for (size_t i=0; i<mesh.getParticles().size(); ++i)
        {
            Particle *p = &mesh.getParticle(i);
            p->a = ngl::Vec3{0.0f, 0.0f, 0.0f};
            p->applyDistanceConstraint();

            if (p->isFixed) { p->applyFixedConstraint(); }
        }

        // set solved particle positions

        // visualise with ngl

        // visualise within gui
}

float ClothSim::getGravity() const
{
    return gravity;
}

ngl::Vec3 ClothSim::getWind() const
{
    return wind;
}

size_t ClothSim::getTimeStep() const
{
    return timeStep;
}

size_t ClothSim::getIterations() const
{
    return solveIterations;
}

void ClothSim::setGravity(float _gravity)
{
    gravity = _gravity;
}

void ClothSim::setWind(ngl::Vec3 _wind)
{
    wind = _wind;
}