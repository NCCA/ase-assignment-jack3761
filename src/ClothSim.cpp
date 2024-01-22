#include "ClothSim.h"

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _solveIterations) : m_gravity{_gravity}, m_wind{_wind}, m_solveIterations{_solveIterations}
{}

ClothSim::ClothSim(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight)
{
	initFixedPoints();
	createNewMesh(_cWidth, _cHeight, _pWidth, _pHeight, 0.1);
}

ClothSim::ClothSim(float _gravity, ngl::Vec3 _wind, size_t _solveIterations, float _cWidth,
                   float _cHeight, size_t _pWidth, size_t _pHeight) : ClothSim(_gravity, _wind, _solveIterations)
{
	initFixedPoints();
	createNewMesh(_cWidth, _cHeight, _pWidth, _pHeight, 0.1);
}

void ClothSim::runSim(float _delta)
{
    m_mesh->applyExternalForces(m_gravity, m_wind, _delta);

    // apply constraints for each particle with particle centric approach
    for (size_t i = 0; i < m_solveIterations; ++i)
    {
        for (size_t j = 0; j < m_mesh->getParticles().size(); ++j)
        {
            Particle* p = &m_mesh->getParticle(j);
            //p->a = ngl::Vec3{ 0.0f, 0.0f, 0.0f };

            // apply  constraints
            if (p->isFixed) { m_mesh->applyFixedConstraint(*p); }
            else
            {
                m_mesh->applyDistanceConstraint(*p);
            }
        }
    }


    // set solved particle positions
    m_mesh->setPositions();
}

void ClothSim::createNewMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight, float _pMass)
{
    /*if (m_mesh != nullptr) {
        m_mesh->clearMesh();
    }*/
    m_mesh = std::make_unique<ClothMesh>(_cWidth, _cHeight, _pWidth, _pHeight);


	initialise();
}

void ClothSim::initFixedPoints()
{
	m_fixedPoints[0]=true;
	m_fixedPoints[1]=true;
	for (size_t i=2; i<=5; ++i)
	{
		m_fixedPoints[i] = false;
	}
}

void ClothSim::initialise()
{
    for (size_t i = 0; i < m_mesh->getParticleWidth(); ++i)
    {
        for (size_t j = 0; j < m_mesh->getParticleHeight(); ++j)
        {
            m_mesh->findNeighbours(i, j);
        }
    }
    //top
    m_mesh->getParticle(m_mesh->getParticleWidth() - 1, m_mesh->getParticleHeight()-1).isFixed = m_fixedPoints[0];
    m_mesh->getParticle(0, m_mesh->getParticleHeight() - 1).isFixed = m_fixedPoints[1];
    m_mesh->getParticle(int((m_mesh->getParticleWidth() - 1)/2), m_mesh->getParticleHeight()-1).isFixed = m_fixedPoints[2];
    // bottom
    m_mesh->getParticle(0, 0).isFixed = m_fixedPoints[3];
    m_mesh->getParticle(m_mesh->getParticleWidth() - 1, 0).isFixed = m_fixedPoints[4];
    m_mesh->getParticle(int((m_mesh->getParticleWidth() - 1)/2), 0).isFixed = m_fixedPoints[5];
}

float ClothSim::getGravity() const
{
    return m_gravity;
}

ngl::Vec3 ClothSim::getWind() const
{
    return m_wind;
}

size_t ClothSim::getIterations() const
{
    return m_solveIterations;
}

void ClothSim::setGravity(float _gravity)
{
    m_gravity = _gravity;
}

void ClothSim::setWind(ngl::Vec3 _wind)
{
    m_wind = _wind;
}

void ClothSim::setFixedPoint(size_t i, bool fixed)
{
    m_fixedPoints[i] = fixed;
}

void ClothSim::setIterations(size_t _solveIterations)
{
    solveIterations = _solveIterations;
}
