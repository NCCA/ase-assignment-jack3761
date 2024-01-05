#include <gtest/gtest.h>
#include "ClothSim.h"

TEST(ClothSim, defCtor)
{
    ClothSim sim;

    EXPECT_FLOAT_EQ(sim.getGravity(), -9.81f);
    EXPECT_FLOAT_EQ(sim.getWind().m_x, 0.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_y, 0.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_z, 1.0f);
    EXPECT_FLOAT_EQ(sim.getTimeStep(), 1);
    EXPECT_FLOAT_EQ(sim.getIterations(), 600);
}

TEST(ClothSim, simParamCtor)
{
    ClothSim sim(9.81f, {2.0f, 3.0f, 4.0f}, 4, 50);

    EXPECT_FLOAT_EQ(sim.getGravity(), 9.81f);
    EXPECT_FLOAT_EQ(sim.getWind().m_x, 2.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_y, 3.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_z, 4.0f);
    EXPECT_FLOAT_EQ(sim.getTimeStep(), 4);
    EXPECT_FLOAT_EQ(sim.getIterations(), 50);
}

TEST(ClothSim, simMeshCtor)
{
    ClothSim sim(4.0, 2.0, 20, 10);

    EXPECT_FLOAT_EQ(sim.mesh.getWidth(), 4.0f);
    EXPECT_FLOAT_EQ(sim.mesh.getHeight(), 2.0f);

    EXPECT_EQ(sim.mesh.getParticleWidth(), 20);
    EXPECT_EQ(sim.mesh.getParticleHeight(), 10);

    EXPECT_FLOAT_EQ(sim.mesh.getWidthStep(), 4.0/20.0f);
    EXPECT_FLOAT_EQ(sim.mesh.getHeightStep(), 2.0/10.0f);

    EXPECT_EQ(sim.mesh.getParticles().size(), 20 * 10);
}

TEST(ClothSim, longCtor)
{
    ClothSim sim(9.81f, {2.0f, 3.0f, 4.0f}, 4, 50, 4.0, 2.0, 20, 10);

    EXPECT_FLOAT_EQ(sim.getGravity(), 9.81f);
    EXPECT_FLOAT_EQ(sim.getWind().m_x, 2.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_y, 3.0f);
    EXPECT_FLOAT_EQ(sim.getWind().m_z, 4.0f);
    EXPECT_FLOAT_EQ(sim.getTimeStep(), 4);
    EXPECT_FLOAT_EQ(sim.getIterations(), 50);

    EXPECT_FLOAT_EQ(sim.mesh.getWidth(), 4.0f);
    EXPECT_FLOAT_EQ(sim.mesh.getHeight(), 2.0f);

    EXPECT_EQ(sim.mesh.getParticleWidth(), 20);
    EXPECT_EQ(sim.mesh.getParticleHeight(), 10);

    EXPECT_FLOAT_EQ(sim.mesh.getWidthStep(), 4.0/20.0f);
    EXPECT_FLOAT_EQ(sim.mesh.getHeightStep(), 2.0/10.0f);

    EXPECT_EQ(sim.mesh.getParticles().size(), 20 * 10);
}

TEST(ClothSim, runSim)
{
    ClothSim sim (-9.81, {0,0,1}, 1, 5, 2, 2, 2, 2);

}