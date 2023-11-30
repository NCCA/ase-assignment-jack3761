#include "ClothSim.h"

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _simDuration) : gravity{_gravity}, wind{_wind}, timeStep{_timeStep}, simIterations{_simDuration}
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
    // to be changed to run indefinitely
    for (size_t i=0; i <= simIterations; ++i)
    {
        // calculate external forces for each particle
        for (Particle p : mesh.getParticles())
        {
            p.applyForces(gravity, wind, timeStep);
            if (p.isFixed) {p.applyFixedConstraint();}
        }

        // find neighbours for each particle

        // apply constraints for each particle
        // start with fixed constraints - top right and left corner to begin
        // solve distance constraints

        // set solved particle positions

        // visualise with ngl

        // visualise within gui
    }
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
    return simIterations;
}

void ClothSim::setGravity(float _gravity)
{
    gravity = _gravity;
}

void ClothSim::setWind(ngl::Vec3 _wind)
{
    wind = _wind;
}