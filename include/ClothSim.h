#ifndef CLOTHSIM_H_
#define CLOTHSIM_H_

#include <ngl/Vec3.h>
#include "ClothMesh.h"

class ClothSim
{
public:
    ClothSim()=default;
    ClothSim(float _gravity, ngl::Vec3 _wind, size_t _solveIterations);
    ClothSim(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight);
    ClothSim(float _gravity, ngl::Vec3 _wind, size_t _solveIterations, float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight);

    void runSim(float _delta);
    void createNewMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight, float _pMass);
    void initialise();
    void initFixedPoints();
    float getGravity() const;
    ngl::Vec3 getWind() const;
    size_t getIterations() const;
    void setGravity(float _gravity);
    void setWind(ngl::Vec3 _wind);
    void setFixedPoint(size_t i, bool fixed);
    std::unique_ptr<ClothMesh> m_mesh;
    void setIterations(size_t _solveIterations);


private:
    float m_gravity = -9.81f;
    ngl::Vec3 m_wind = {0.0, 0.0, 1.0};
    size_t m_solveIterations = 1000;
    bool m_fixedPoints[6];

};

#endif
