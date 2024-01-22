#include "ClothMesh.h"
#include <iomanip>
#include <ngl/VAOFactory.h>



ClothMesh::ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight, float _pMass) : m_cWidth{_cWidth}, m_cHeight{_cHeight}, m_pWidth{_pWidth}, m_pHeight{_pHeight}
{
    m_widthStep = m_cWidth / static_cast<float>(m_pWidth);
    m_heightStep = m_cHeight / static_cast<float>(m_pHeight);

    float px = -m_cWidth * 0.5f + m_widthStep * 0.5f;
    float py = -m_cHeight * 0.5f + m_heightStep * 0.5f;

    for (size_t y = 0; y < m_pHeight; ++y)
    {
        for (size_t x = 0; x < m_pWidth; ++x)
        {
            Particle p;
            p.m_pos.m_x = px;
            p.m_p_pos.m_x = px;
            p.m_pos.m_y = py;
            p.m_p_pos.m_y = py;
            m_particles.push_back(p);

            px += m_widthStep;
        }
        px = -m_cWidth * 0.5f + m_widthStep * 0.5f;
        py += m_heightStep;
    }

    m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}


void ClothMesh::drawGL()
{
    glPointSize(4.0);
    m_vao->bind();
    m_vao->setData(ngl::AbstractVAO::VertexData(m_particles.size()*sizeof(Particle), m_particles[0].m_pos.m_x));
    m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Particle), 0);
    m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(Particle), 6);

    m_vao->setNumIndices(m_particles.size());
    m_vao->draw();
    m_vao->unbind();
}

void ClothMesh::findNeighbours(size_t _x, size_t _y)
{
    Particle *p = &getParticle(_x, _y);
    if (_x > 0)
    {
        p->m_neighbours.push_back(&m_particles[(_x-1) + _y * m_pWidth]);
        p->m_yNeighbours.push_back(false); //left
    }
    if (_x < m_pWidth -1)
    {
        p->m_neighbours.push_back(&m_particles[(_x+1) + _y * m_pWidth]);
        p->m_yNeighbours.push_back(false); //right
    }
    if (_y < m_pHeight -1)
    {
        p->m_neighbours.push_back(&m_particles[_x + (_y+1)*m_pWidth]);
        p->m_yNeighbours.push_back(true); //above
    }
    if (_y > 0)
    {
        p->m_neighbours.push_back(&m_particles[_x + (_y-1)*m_pWidth]);
        p->m_yNeighbours.push_back(true); //below
    }
}

void ClothMesh::applyExternalForces(float _gravity, ngl::Vec3 _wind, float _timeStep)
{
    for (Particle& p : m_particles)
    {
        p.m_v += ngl::Vec3{ 0, _gravity, 0 } *_timeStep + _wind * _timeStep;
        p.m_p_pos += p.m_v * _timeStep;
    }
}

void ClothMesh::applyFixedConstraint(Particle &p)
{
    ngl::Vec3 dt = p.m_pos - p.m_p_pos;
    p.m_p_pos += dt;
}

void ClothMesh::applyDistanceConstraint(Particle& p)
{
    for (size_t i=0; i<p.m_neighbours.size(); ++i)
    {
      Particle* n = p.m_neighbours[i];
      ngl::Vec3 delta = p.m_p_pos - n->m_p_pos;
      float dist = delta.length();
      float diff = 0;

			if (p.m_yNeighbours[i])
			{
				diff = (dist - m_heightStep) / dist;
			}
			else
			{
				diff = (dist - m_widthStep) / dist;
			}

			float invMassSum = 1.0f / (p.getInvMass() + n->getInvMass());

      ngl::Vec3 correction1 = -p.getInvMass() * invMassSum * diff * delta;
      ngl::Vec3 correction2 = n->getInvMass() * invMassSum * diff * delta;

		p.m_p_pos += correction1;
        if (!(n->isFixed))
        {
            n->m_p_pos += correction2;
        }
	}
}

void ClothMesh::setPositions()
{
    for (Particle &p : m_particles)
    {
        p.m_pos = p.m_p_pos;
    }
}

void ClothMesh::draw()
{
    size_t wCount = 0;

    for (Particle p : m_particles)
    {
        if (wCount < m_pWidth)
        {
            std::cout << std::fixed
                      << std::setprecision(2) << (p.m_pos.m_x <= 0 ? " (" : " ( ")<< p.m_pos.m_x << "," << (p.m_pos.m_y <= 0 ? "" : " ") << p.m_pos.m_y << "," << (p.m_pos.m_z <= 0 ? "" : " ") << p.m_pos.m_z << ") *";
            wCount++;
        }
        else
        {
            std::cout << "\n";
            std::cout << std::fixed
                      << std::setprecision(2) << (p.m_pos.m_x <= 0 ? " (" : " ( ")<< p.m_pos.m_x << "," << (p.m_pos.m_y <= 0 ? "" : " ") << p.m_pos.m_y << "," << (p.m_pos.m_z <= 0 ? "" : " ") << p.m_pos.m_z << ") *";
            wCount = 1;
        }
    }
}


float ClothMesh::getWidth() const {
    return m_cWidth;
}

float ClothMesh::getHeight() const {
    return m_cHeight;
}

size_t ClothMesh::getParticleWidth() const {
    return m_pWidth;
}

size_t ClothMesh::getParticleHeight() const {
    return m_pHeight;
}

std::vector<Particle>& ClothMesh::getParticles() {
    return m_particles;
}


Particle& ClothMesh::getParticle(size_t _index)
{
    return m_particles[_index];
}

Particle& ClothMesh::getParticle(size_t _x, size_t _y)
{
    size_t index = _x + _y * m_pWidth;
    return getParticle(index);
}


float ClothMesh::getWidthStep() const
{
    return m_widthStep;
}

float ClothMesh::getHeightStep() const
{
    return m_heightStep;
}
