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

    EXPECT_FLOAT_EQ(p.mass, 0.1f);

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

    EXPECT_FLOAT_EQ(p.mass, 0.1f);

    EXPECT_FLOAT_EQ(p.isFixed, false);

}


TEST(ClothMesh, ctor)
{
    ClothMesh clothMesh(2.0, 4.0, 10, 20);

    EXPECT_FLOAT_EQ(clothMesh.getWidth(), 2.0f);
    EXPECT_FLOAT_EQ(clothMesh.getHeight(), 4.0f);

    EXPECT_EQ(clothMesh.getParticleWidth(), 10);
    EXPECT_EQ(clothMesh.getParticleHeight(), 20);

    EXPECT_FLOAT_EQ(clothMesh.getStep(), 0.2f);

    EXPECT_EQ(clothMesh.getParticles().size(), 10 * 20);
}

TEST(ClothMesh, find4Neighbours)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);

    Particle *p = &clothMesh.getParticle(1,1);

    clothMesh.findNeighbours(1, 1);

    EXPECT_EQ(4, p->neighbours.size());


    EXPECT_EQ(&clothMesh.getParticle(0,1), p->neighbours[0]);
    EXPECT_EQ(&clothMesh.getParticle(2,1), p->neighbours[1]);
    EXPECT_EQ(&clothMesh.getParticle(1,2), p->neighbours[2]);
    EXPECT_EQ(&clothMesh.getParticle(1,0), p->neighbours[3]);
}

TEST(ClothMesh, find3Neighbours)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);

    Particle *p = &clothMesh.getParticle(0,1);

    clothMesh.findNeighbours(0, 1);

    EXPECT_EQ(3, p->neighbours.size());

    EXPECT_EQ(&clothMesh.getParticle(1,1), p->neighbours[0]);
    EXPECT_EQ(&clothMesh.getParticle(0,2), p->neighbours[1]);
    EXPECT_EQ(&clothMesh.getParticle(0,0), p->neighbours[2]);
}

TEST(ClothMesh, find2Neighbours)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);

    Particle *p = &clothMesh.getParticle(0,0);

    clothMesh.findNeighbours(0, 0);

    EXPECT_EQ(2, p->neighbours.size());

    EXPECT_EQ(&clothMesh.getParticle(1,0), p->neighbours[0]);
    EXPECT_EQ(&clothMesh.getParticle(0,1), p->neighbours[1]);

}


TEST(ClothMesh, applyForces)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);
    Particle& p = clothMesh.getParticle(1, 1);

    clothMesh.applyExternalForces(-9.81, {0, 0, 1}, 1);

    EXPECT_FLOAT_EQ(p.v.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.v.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.v.m_z, 1.0);


    EXPECT_FLOAT_EQ(p.p_pos.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 1.0);

}

TEST(ClothMesh, applyFixedConstraint)
{
    ClothMesh clothMesh(3.0, 3.0, 3, 3);
    Particle& p = clothMesh.getParticle(2,2);
    clothMesh.applyExternalForces(-9.81, {0, 0, 1}, 1);
    clothMesh.applyFixedConstraint(p);

    EXPECT_FLOAT_EQ(p.v.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.v.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.v.m_z, 1.0);


    EXPECT_FLOAT_EQ(p.p_pos.m_x, 1.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, 1.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 0.0);

    p = clothMesh.getParticle(1,1);

    EXPECT_FLOAT_EQ(p.p_pos.m_x, 0.0);
    EXPECT_FLOAT_EQ(p.p_pos.m_y, -9.81);
    EXPECT_FLOAT_EQ(p.p_pos.m_z, 1.0);
}

TEST(ClothMesh, applyDistanceConstraint) 
{
   
}

TEST(ClothMesh, clearMesh)
{		
    ClothMesh clothMesh(2.0, 4.0, 10, 20);
	clothMesh.clearMesh();

	EXPECT_FLOAT_EQ(clothMesh.getWidth(), 0.0f);
	EXPECT_FLOAT_EQ(clothMesh.getHeight(), 0.0f);

	EXPECT_EQ(clothMesh.getParticleWidth(), 0);
	EXPECT_EQ(clothMesh.getParticleHeight(), 0);

	EXPECT_FLOAT_EQ(clothMesh.getStep(), 0.0f);

	EXPECT_EQ(clothMesh.getParticles().size(), 0);
	
}





