#ifndef CLOTHSIM_H_
#define CLOTHSIM_H_

#include "Vec3.h"
#include "ClothMesh.h"

class ClothSim
{
public:
    ClothSim()=default;
    void runSim();
    void solveConstraints();
    float getGravity() const;
    Vec3 getWind() const;
    float setGravity();
    Vec3 setWind();

private:
    ClothMesh mesh;
    float gravity = -9.81f;
    Vec3 wind;
};

#endif