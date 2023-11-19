#ifndef CLOTHSIM_H_
#define CLOTHSIM_H_

#include <ngl/Vec3.h>
#include "ClothMesh.h"

class ClothSim
{
public:
    ClothSim()=default;
    void runSim();
    void solveConstraints();
    float getGravity() const;
    ngl::Vec3 getWind() const;
    float setGravity();
    ngl::Vec3 setWind();

private:
    ClothMesh mesh;
    float gravity = -9.81f;
    ngl::Vec3 wind;
};

#endif