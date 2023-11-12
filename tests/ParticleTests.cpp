#include <gtest/gtest.h>
#include "Particle.h"
#include "ClothMesh.h"

TEST(Particle, ctor)
{
    Particle p;

    EXPECT_FLOAT_EQ(p.pos.x, 0.0f);
    EXPECT_FLOAT_EQ(p.pos.y, 0.0f);
    EXPECT_FLOAT_EQ(p.pos.z, 0.0f);

    EXPECT_FLOAT_EQ(p.dir.x, 0.0f);
    EXPECT_FLOAT_EQ(p.dir.y, 0.0f);
    EXPECT_FLOAT_EQ(p.dir.z, 0.0f);

    EXPECT_FLOAT_EQ(p.mass, 1.0f);
}

TEST(Vec3, ctor)
{
    Vec3 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(ClothMesh, ctor)
{
    ClothMesh clothMesh(2.0, 4.0, 10, 20);

    EXPECT_FLOAT_EQ(clothMesh.getWidth(), 2.0f);
    EXPECT_FLOAT_EQ(clothMesh.getHeight(), 4.0f);
    EXPECT_EQ(clothMesh.getParticleWidth(), 10);
    EXPECT_EQ(clothMesh.getParticleHeight(), 20);
    EXPECT_EQ(clothMesh.getParticles().size(), 10 * 20);

//    clothMesh.draw();
}
