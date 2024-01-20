#ifndef CLOTHMESH_H_
#define CLOTHMESH_H_

#include <vector>
#include <iostream>
#include <ngl/AbstractVAO.h>
#include "Particle.h"

class ClothMesh
{
public:
    ClothMesh()=default;
    ClothMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight);
    //~ClothMesh();
    float getWidth() const;
    float getHeight() const;
    size_t getParticleWidth() const;
    size_t getParticleHeight() const;
    float getWidthStep() const;
    float getHeightStep() const;
    size_t numParticles;
    std::vector<Particle>& getParticles();
    Particle& getParticle(size_t _index);
    Particle& getParticle(size_t _x, size_t _y);
    void setPositions();

    void findNeighbours(size_t _x, size_t _y);
    void applyExternalForces(float _gravity, ngl::Vec3 _wind, float _timeStep);
    void applyFixedConstraint(Particle &p);
    void applyDistanceConstraint(Particle &p);
    void setupMesh();
    void clearMesh();
    void draw();
    void drawGL();

private:
    float cWidth;
    float cHeight;
    size_t pWidth;
    size_t pHeight;
    float step;
    std::vector<Particle> particles;
    std::unique_ptr<ngl::AbstractVAO> m_vao;

};

#endif
