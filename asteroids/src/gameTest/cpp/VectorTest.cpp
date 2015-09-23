#include <gmock/gmock.h>
#include <Vector.hpp>
#include <sstream>

using namespace pjm;

TEST(VectorTest, InitialisesMembers)
{
    Vector v(5.0f, 7.0f);
    EXPECT_EQ(5.0f, v.x);
    EXPECT_EQ(7.0f, v.y);
}

TEST(VectorTest, ImplementsCopyOperator)
{
    Vector v1(3.4f, 2.5f);
    Vector v2 = v1;
    EXPECT_EQ(3.4f, v2.x);
    EXPECT_EQ(2.5f, v2.y);
}

TEST(VectorTest, ImplementsEquals)
{
    Vector v1(2.0f, 4.0f);
    Vector v2(3.0f, 4.0f);
    Vector v3(2.0f, 5.0f);
    Vector v4(7.0f, 9.0f);
    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
}

TEST(VectorTest, PrettyPrints)
{
    Vector v(5.2f, 7.9f);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ("(5.2,7.9)", ss.str());
}

TEST(VectorTest, ImplementsAdditionAssignment)
{
    Vector v1(3.2f, 4.4f);
    Vector v2(2.3f, 1.2f);
    v1 += v2;
    EXPECT_EQ(Vector(5.5f, 5.6f), v1);
    EXPECT_EQ(Vector(2.3f, 1.2f), v2);
}

TEST(VectorTest, ImplementsSubtractionAssignment)
{
    Vector v1(3.2f, 4.4f);
    Vector v2(2.3f, 1.2f);
    v1 -= v2;
    EXPECT_EQ(Vector(0.9f, 3.2f), v1);
    EXPECT_EQ(Vector(2.3f, 1.2f), v2);
}

TEST(VectorTest, ImplementsScalarMultiplicationAssignment)
{
    Vector v1(3.2f, 4.4f);
    v1 *= 3;
    EXPECT_EQ(Vector(9.6f, 13.2f), v1);
}

TEST(VectorTest, ImplementsFloatMultiplicationAssignment)
{
    Vector v1(3.2f, 4.4f);
    v1 *= 0.5f;
    EXPECT_EQ(Vector(1.6f, 2.2f), v1);
}

TEST(VectorTest, ImplementsAddition)
{
    Vector v1(3.2f, 4.4f);
    Vector v2(2.3f, 1.2f);
    Vector v3 = v1 + v2; 
    EXPECT_EQ(Vector(5.5f, 5.6f), v3);
}

TEST(VectorTest, ImplementsSubtraction)
{
    Vector v1(3.2f, 4.4f);
    Vector v2(2.3f, 1.2f);
    Vector v3 = v1 - v2; 
    EXPECT_EQ(Vector(0.9f, 3.2f), v3);
}

TEST(VectorTest, ImplementsScalarMultiplication)
{
    Vector v1(3.2f, 4.4f);
    Vector v3 = v1*3;
    EXPECT_EQ(Vector(9.6f, 13.2f), v3);
}

TEST(VectorTest, ComputesSquareSum)
{
    Vector v1(5.0f, 2.0f);
    EXPECT_EQ(29.0f, v1.squareSum());
}
