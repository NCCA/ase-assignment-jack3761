#ifndef CLOTHMESH_H_
#define CLOTHMESH_H_

#include <vector>
#include <iostream>
#include "Particle.h"

class ClothMesh
{
public:
    ClothMesh()=default;
    ClothMesh(size_t _rows, size_t _cols, size_t spacing);

private:
    std::vector<Particle> particles;
};

#endif