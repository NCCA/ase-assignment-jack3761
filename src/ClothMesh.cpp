#include "ClothMesh.h"

ClothMesh::ClothMesh(size_t _rows, size_t _cols, size_t spacing)
{
    for (auto i=0; i<_rows; ++i)
    {
        for (auto j=0; j<_cols; ++j)
        {
            Particle p;
            p.pos.x = static_cast<float>(i) * static_cast<float>(spacing);
            p.pos.y = static_cast<float>(j) * static_cast<float>(spacing);
            particles.push_back(p);
        }
    }
}