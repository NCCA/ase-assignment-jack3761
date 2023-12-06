#include <gtest/gtest.h>
#include "Particle.h"
#include "ClothMesh.h"

TEST(Particle, defCtor)
{
    Particle p;

    EXPECT_FLOAT_EQ(p.pos.m_x, 0.0f);
    EXPECT_FLOAT_EQ(p.pos.m_y, 0.0f);
    EXPECT_FLOAT_EQ(p.pos.m_z, 0.0f);

    EXPECT_FLOAT_EQ(p.p_pos.m_x, 0.0f);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, 0.0f);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 0.0f);

    EXPECT_FLOAT_EQ(p.v.m_x, 0.0f);
    EXPECT_FLOAT_EQ(p.v.m_y, 0.0f);
    EXPECT_FLOAT_EQ(p.v.m_z, 0.0f);

    EXPECT_FLOAT_EQ(p.mass, 1.0f);

    EXPECT_FLOAT_EQ(p.isFixed, false);
}

TEST(Particle, ctor)
{
    Particle p(1.0f, 2.0f, 3.0f, 1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(p.pos.m_x, 1.0f);
    EXPECT_FLOAT_EQ(p.pos.m_y, 2.0f);
    EXPECT_FLOAT_EQ(p.pos.m_z, 3.0f);

    EXPECT_FLOAT_EQ(p.p_pos.m_x, 1.0f);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, 2.0f);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 3.0f);

    EXPECT_FLOAT_EQ(p.v.m_x, 1.0f);
    EXPECT_FLOAT_EQ(p.v.m_y, 2.0f);
    EXPECT_FLOAT_EQ(p.v.m_z, 3.0f);

    EXPECT_FLOAT_EQ(p.mass, 1.0f);

    EXPECT_FLOAT_EQ(p.isFixed, false);

}


TEST(ClothMesh, ctor)
{
    ClothMesh clothMesh(2.0, 4.0, 10, 20);

    EXPECT_FLOAT_EQ(clothMesh.getWidth(), 2.0f);
    EXPECT_FLOAT_EQ(clothMesh.getHeight(), 4.0f);

    EXPECT_EQ(clothMesh.getParticleWidth(), 10);
    EXPECT_EQ(clothMesh.getParticleHeight(), 20);

    EXPECT_FLOAT_EQ(clothMesh.getWidthStep(), 2.0/10.0f);
    EXPECT_FLOAT_EQ(clothMesh.getHeightStep(), 4.0/20.0f);

    EXPECT_EQ(clothMesh.getParticles().size(), 10 * 20);

//    clothMesh.draw();
}

TEST(ClothMesh, findNeighbours)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);

    Particle *p = &clothMesh.getParticle(1,1);

    p->draw();

    clothMesh.findNeighbours(p, 1, 1);

    EXPECT_EQ(&clothMesh.getParticle(0,1), p->neighbours[0]);
    EXPECT_EQ(&clothMesh.getParticle(2,1), p->neighbours[1]);
    EXPECT_EQ(&clothMesh.getParticle(1,2), p->neighbours[2]);
    EXPECT_EQ(&clothMesh.getParticle(1,0), p->neighbours[3]);

    EXPECT_EQ(4, p->neighbours.size());

    clothMesh.draw();
}

TEST(Particle, applyForces)
{
    Particle p(1.0, 1.0, 0.0);

    p.applyForces(-9.81, {0, 0, 1}, 1);

    EXPECT_FLOAT_EQ(p.v.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.v.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.v.m_z, 1.0);


    EXPECT_FLOAT_EQ(p.p_pos.m_x, 1.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, -8.81);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 1.0);
}

TEST(Particle, applyFixedConstraint)
{
    Particle p(1.0, 1.0, 0.0);
    p.applyForces(-9.81, {0, 0, 1}, 1);
    p.applyFixedConstraint();

    EXPECT_FLOAT_EQ(p.v.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.v.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.v.m_z, 1.0);


    EXPECT_FLOAT_EQ(p.p_pos.m_x, 1.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, 1.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 0.0);
}




