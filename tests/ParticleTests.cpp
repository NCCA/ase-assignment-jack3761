#include <gtest/gtest.h>
#include "Particle.h"
#include "ClothMesh.h"

TEST(Particle, defCtor)
{
    Particle p;

    EXPECT_FLOAT_EQ(p.pos[0], 0.0f);
    EXPECT_FLOAT_EQ(p.pos[1], 0.0f);
    EXPECT_FLOAT_EQ(p.pos[2], 0.0f);

    EXPECT_FLOAT_EQ(p.dir[0], 0.0f);
    EXPECT_FLOAT_EQ(p.dir[1], 0.0f);
    EXPECT_FLOAT_EQ(p.dir[2], 0.0f);

    EXPECT_FLOAT_EQ(p.mass, 1.0f);
}

TEST(Particle, ctor)
{
    Particle p(1.0f, 2.0f, 3.0f, 1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(p.pos[0], 1.0f);
    EXPECT_FLOAT_EQ(p.pos[1], 2.0f);
    EXPECT_FLOAT_EQ(p.pos[2], 3.0f);

    EXPECT_FLOAT_EQ(p.dir[0], 1.0f);
    EXPECT_FLOAT_EQ(p.dir[1], 2.0f);
    EXPECT_FLOAT_EQ(p.dir[2], 3.0f);

    EXPECT_FLOAT_EQ(p.mass, 1.0f);
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

    clothMesh.draw();
}
