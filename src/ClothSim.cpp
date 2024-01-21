#include "ClothSim.h"

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _solveIterations) : gravity{_gravity}, wind{_wind}, timeStep{_timeStep}, solveIterations{_solveIterations}
{}

ClothSim::ClothSim(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight)
{
	initFixedPoints();
	createNewMesh(_cWidth, _cHeight, _pWidth, _pHeight, 0.1);
}

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _timeStep, size_t _solveIterations, float _cWidth,
                   float _cHeight, size_t _pWidth, size_t _pHeight) : ClothSim(_gravity, _wind, _timeStep, _solveIterations)
{
	initFixedPoints();
	createNewMesh(_cWidth, _cHeight, _pWidth, _pHeight, 0.1);
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
            //p->a = ngl::Vec3{ 0.0f, 0.0f, 0.0f };

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

void ClothSim::createNewMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight, float _pMass)
{
		mesh.clearMesh();
		mesh = ClothMesh(_cWidth, _cHeight, _pWidth, _pHeight, _pMass);

		initialise();
}

void ClothSim::initFixedPoints()
{
		fixedPoints[0]=true;
		fixedPoints[1]=true;
		for (size_t i=2; i<=6; ++i)
		{
				fixedPoints[i] = false;
		}
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
    mesh.getParticle(mesh.getParticleWidth() - 1, mesh.getParticleHeight()-1).isFixed = fixedPoints[0];
    mesh.getParticle(0, mesh.getParticleHeight() - 1).isFixed = fixedPoints[1];
    mesh.getParticle(int((mesh.getParticleWidth() - 1)/2), mesh.getParticleHeight()-1).isFixed = fixedPoints[2];
    // bottom
    mesh.getParticle(0, 0).isFixed = fixedPoints[3];
    mesh.getParticle(mesh.getParticleWidth() - 1, 0).isFixed = fixedPoints[4];
    mesh.getParticle(int((mesh.getParticleWidth() - 1)/2), 0).isFixed = fixedPoints[5];
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

void ClothSim::setFixedPoint(size_t i, bool fixed)
{
    fixedPoints[i] = fixed;
}

void ClothSim::setIterations(size_t _solveIterations)
{
    solveIterations = _solveIterations;
}
