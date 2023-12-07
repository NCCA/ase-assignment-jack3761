#ifndef CLOTHMESH_H_
#define CLOTHMESH_H_

#include <vector>
#include <iostream>
#include "Particle.h"

class ClothMesh
{
public:
    ClothMesh()=default;
    ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight);
    float getWidth() const;
    float getHeight() const;
    size_t getParticleWidth() const;
    size_t getParticleHeight() const;
    float getWidthStep() const;
    float getHeightStep() const;
    std::vector<Particle>& getParticles();
    Particle& getParticle(size_t _index);
    Particle& getParticle(size_t _x, size_t _y);
        void findNeighbours(size_t _x, size_t _y);
    void draw();

private:
    float cWidth;
    float cHeight;
    size_t pWidth;
    size_t pHeight;
    float widthStep;
    float heightStep;
    std::vector<Particle> particles;
};

#endif