#include "ClothSim.h"

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _solveIterations) : gravity{_gravity}, wind{_wind}, timeStep{_timeStep}, solveIterations{_solveIterations}
{}

ClothSim::ClothSim(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight)
{
    mesh = ClothMesh(_cWidth, _cHeight, _pWidth, _pHeight);
}

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _solveIterations, float _cWidth,
                   float _cHeight, size_t _pWidth, size_t _pHeight) : ClothSim(_gravity, _wind, _timeStep, _solveIterations)
{
    mesh = ClothMesh(_cWidth, _cHeight, _pWidth, _pHeight);
}

void ClothSim::runSim(float _delta)
{
    mesh.applyExternalForces(gravity, wind, _delta);

    // apply constraints for each particle with particle centric approach
    for (size_t i = 0; i < solveIterations; ++i)
    {
        for (size_t j = 0; j < mesh.getParticles().size(); ++j)
        {
            Particle* p = &mesh.getParticle(j);
            p->a = ngl::Vec3{ 0.0f, 0.0f, 0.0f };

            // apply  constraints
            if (p->isFixed) { mesh.applyFixedConstraint(*p); }
            else
            {
                mesh.applyDistanceConstraint(*p);
            }
        }
    }


    // set solved particle positions
    mesh.setPositions();
}

void ClothSim::initialise()
{
    for (size_t i = 0; i < mesh.getParticleWidth(); ++i)
    {
        for (size_t j = 0; j < mesh.getParticleHeight(); ++j)
        {
            mesh.findNeighbours(i, j);
        }
    }
    //top
    mesh.getParticle(mesh.getParticleWidth() - 1, mesh.getParticleHeight()-1).isFixed = true;
    mesh.getParticle(0, mesh.getParticleHeight() - 1).isFixed = true;
    //middle
    //mesh.getParticle(int((mesh.getParticleWidth() - 1)/2), mesh.getParticleHeight()-1).isFixed = true;
    // bottom
    mesh.getParticle(0, 0).isFixed = true;
    mesh.getParticle(mesh.getParticleWidth() - 1, 0).isFixed = true;
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
