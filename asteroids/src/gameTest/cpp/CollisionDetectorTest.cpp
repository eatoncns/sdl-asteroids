#include <gmock/gmock.h>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>

using namespace pjm;
using ::testing::Eq;

class CollisionDetectorTest : public ::testing::Test
{
    protected:

        CollisionDetector _collisionDetector;
};

TEST_F(CollisionDetectorTest, ReturnsFalseWhenNoOverlapAlongEitherAxis)
{
    Rectangle rect1(5, 5, 10, 15);
    Rectangle rect2(100, 100, 10, 15);
    EXPECT_THAT(_collisionDetector.areColliding(rect1, rect2), Eq(false));
}

TEST_F(CollisionDetectorTest, ReturnsFalseWhenNoOverlapAlongYAxis)
{
    Rectangle rect1(5, 5, 10, 15);
    Rectangle rect2(5, 100, 10, 15);
    EXPECT_THAT(_collisionDetector.areColliding(rect1, rect2), Eq(false));
}

TEST_F(CollisionDetectorTest, ReturnsFalseWhenNoOverlapAlongXAxis)
{
    Rectangle rect1(5, 100, 10, 15);
    Rectangle rect2(100, 100, 10, 15);
    EXPECT_THAT(_collisionDetector.areColliding(rect1, rect2), Eq(false));
}

TEST_F(CollisionDetectorTest, ReturnsTrueWhenOverlappingAlongBothAxis)
{
    Rectangle rect1(5, 5, 10, 15);
    Rectangle rect2(10, 15, 20, 20);
    EXPECT_THAT(_collisionDetector.areColliding(rect1, rect2), Eq(true));
}
