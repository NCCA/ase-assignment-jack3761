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
    ClothMesh mesh(8, 10, 5);
}
