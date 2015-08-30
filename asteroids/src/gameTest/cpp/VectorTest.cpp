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

TEST(VectorTest, ImplementsCompoundAssignment)
{
    Vector v1(3.2f, 4.4f);
    Vector v2(2.3f, 1.2f);
    v1 += v2;
    EXPECT_EQ(Vector(5.5f, 5.6f), v1);
    EXPECT_EQ(Vector(2.3f, 1.2f), v2);
}
