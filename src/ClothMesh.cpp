#include "ClothMesh.h"
#include <iomanip>


ClothMesh::ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight) : cWidth{_cWidth}, cHeight{_cHeight}, pWidth{_pWidth}, pHeight{_pHeight}
{
    widthStep = cWidth / static_cast<float>(pWidth);
    heightStep = cHeight / static_cast<float>(pHeight);

    float px = -(cWidth * 0.5f) + widthStep * 0.5f;
    float py = -(cHeight * 0.5f) + heightStep * 0.5f;

    for (size_t y = 0; y < pHeight; ++y)
    {
        for (size_t x = 0; x < pWidth; ++x)
        {
            Particle p;
            p.pos.m_x = px;
            p.pos.m_y = py;
            particles.push_back(p);

            px += widthStep;
        }
        px = -(cWidth / 2.0f) + widthStep * 0.5f;
        py += heightStep;
    }

    numParticles = particles.size();


}

void ClothMesh::findNeighbours(size_t _x, size_t _y)
{
    Particle *p = &getParticle(_x, _y);
    if (_x > 0) p->neighbours.push_back(&particles[(_x-1) + _y * pWidth]); //left
    if (_x < pWidth -1) p->neighbours.push_back(&particles[(_x+1) + _y * pWidth]); //right
    if (_y < pHeight -1) p->neighbours.push_back(&particles[_x + (_y+1)*pWidth]); //above
    if (_y > 0) p->neighbours.push_back(&particles[_x + (_y-1)*pWidth]); //below
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