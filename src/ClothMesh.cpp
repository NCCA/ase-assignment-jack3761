#include "ClothMesh.h"
#include <iomanip>


ClothMesh::ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight) : cWidth{_cWidth}, cHeight{_cHeight}, pWidth{_pWidth}, pHeight{_pHeight}
{
    widthStep = cWidth / static_cast<float>(pWidth);
    heightStep = cHeight / static_cast<float>(pHeight);

    float px=-(cWidth*0.5f);
    float py=-(cHeight*0.5f);

    for(size_t y=0; y<pHeight; ++y)
    {
        for(size_t x=0; x<pWidth; ++x)
        {
            Particle p;
            p.pos.m_x = px;
            p.pos.m_y = py;
            particles.push_back(p);

            px += widthStep;
        }
        px = -(cWidth/2.0f);
        py += heightStep;
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

const std::vector<Particle>& ClothMesh::getParticles() const {
    return particles;
}

float ClothMesh::getWidthStep() const
{
    return widthStep;
}

float ClothMesh::getHeightStep() const
{
    return heightStep;
}