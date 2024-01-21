#include "ClothMesh.h"
#include <iomanip>
#include <ngl/VAOFactory.h>



ClothMesh::ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight, float _pMass) : cWidth{_cWidth}, cHeight{_cHeight}, pWidth{_pWidth}, pHeight{_pHeight}
{
    widthStep = cWidth / static_cast<float>(pWidth);
    heightStep = cHeight / static_cast<float>(pHeight);

    float px = -cWidth * 0.5f + widthStep * 0.5f;
    float py = -cHeight * 0.5f + heightStep * 0.5f;

    for (size_t y = 0; y < pHeight; ++y)
    {
        for (size_t x = 0; x < pWidth; ++x)
        {
            Particle p;
            p.pos.m_x = px;
            p.p_pos.m_x = px;
            p.pos.m_y = py;
            p.p_pos.m_y = py;
            p.mass = _pMass;
            particles.push_back(p);

            px += widthStep;
        }
        px = -cWidth * 0.5f + widthStep * 0.5f;
        py += heightStep;
    }

    numParticles = particles.size();

    m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}


void ClothMesh::drawGL()
{
    glPointSize(4.0);
    m_vao->bind();
    m_vao->setData(ngl::AbstractVAO::VertexData(particles.size()*sizeof(Particle), particles[0].pos.m_x));
    m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Particle), 0);

    m_vao->setNumIndices(particles.size());
    m_vao->draw();
    m_vao->unbind();
}

void ClothMesh::findNeighbours(size_t _x, size_t _y)
{
    Particle *p = &getParticle(_x, _y);
    if (_x > 0)
    {
        p->neighbours.push_back(&particles[(_x-1) + _y * pWidth]);
        p->yNeighbours.push_back(false); //left
    }
    if (_x < pWidth -1)
    {
        p->neighbours.push_back(&particles[(_x+1) + _y * pWidth]);
        p->yNeighbours.push_back(false); //right
    }
    if (_y < pHeight -1)
    {
        p->neighbours.push_back(&particles[_x + (_y+1)*pWidth]);
        p->yNeighbours.push_back(true); //above
    }
    if (_y > 0)
    {
        p->neighbours.push_back(&particles[_x + (_y-1)*pWidth]);
        p->yNeighbours.push_back(true); //below
    }
}

void ClothMesh::applyExternalForces(float _gravity, ngl::Vec3 _wind, float _timeStep)
{
    for (Particle& p : particles)
    {
        p.v += ngl::Vec3{ 0, _gravity, 0 } *_timeStep + _wind * _timeStep;
        p.p_pos += p.v * _timeStep;
    }
}

void ClothMesh::applyFixedConstraint(Particle &p)
{
    ngl::Vec3 dt = p.pos - p.p_pos;
    p.p_pos += dt;
}

void ClothMesh::applyDistanceConstraint(Particle& p)
{
    for (size_t i=0; i<p.neighbours.size(); ++i)
    {
      Particle* n = p.neighbours[i];
      ngl::Vec3 delta = p.p_pos - n->p_pos;
      float dist = delta.length();
      float diff = 0;

			if (p.yNeighbours[i])
			{
				diff = (dist - heightStep) / dist;
			}
			else
			{
				diff = (dist - widthStep) / dist;
			}

			float invMassSum = 1.0f / (p.getInvMass() + n->getInvMass());

      ngl::Vec3 correction1 = -p.getInvMass() * invMassSum * diff * delta;
      ngl::Vec3 correction2 = n->getInvMass() * invMassSum * diff * delta;

		p.p_pos += correction1;
        if (!(n->isFixed))
        {
            n->p_pos += correction2;
        }
	}
}

void ClothMesh::setPositions()
{
    for (Particle &p : particles)
    {
        p.pos = p.p_pos;
    }
}

void ClothMesh::draw()
{
    size_t wCount = 0;

    for (Particle p : particles)
    {
        if (wCount < pWidth)
        {
            std::cout << std::fixed
                      << std::setprecision(2) << (p.pos.m_x <= 0 ? " (" : " ( ")<< p.pos.m_x << "," << (p.pos.m_y <= 0 ? "" : " ") << p.pos.m_y << "," << (p.pos.m_z <= 0 ? "" : " ") << p.pos.m_z << ") *";
            wCount++;
        }
        else
        {
            std::cout << "\n";
            std::cout << std::fixed
                      << std::setprecision(2) << (p.pos.m_x <= 0 ? " (" : " ( ")<< p.pos.m_x << "," << (p.pos.m_y <= 0 ? "" : " ") << p.pos.m_y << "," << (p.pos.m_z <= 0 ? "" : " ") << p.pos.m_z << ") *";
            wCount = 1;
        }
    }
}

void ClothMesh::clearMesh()
{
		cWidth = 0.0f;
		cHeight = 0.0f;
		pWidth = 0;
		pHeight = 0;
		widthStep = 0;
        heightStep = 0;

		particles.clear();
        if (m_vao != nullptr) {
            m_vao->removeVAO();
        }
}


float ClothMesh::getWidth() const {
    return cWidth;
}

float ClothMesh::getHeight() const {
    return cHeight;
}

size_t ClothMesh::getParticleWidth() const {
    return pWidth;
}

size_t ClothMesh::getParticleHeight() const {
    return pHeight;
}

std::vector<Particle>& ClothMesh::getParticles() {
    return particles;
}


Particle& ClothMesh::getParticle(size_t _index)
{
    return particles[_index];
}

Particle& ClothMesh::getParticle(size_t _x, size_t _y)
{
    size_t index = _x + _y * pWidth;
    return getParticle(index);
}


float ClothMesh::getWidthStep() const
{
    return widthStep;
}

float ClothMesh::getHeightStep() const
{
    return heightStep;
}
