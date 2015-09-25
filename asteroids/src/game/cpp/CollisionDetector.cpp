#include <CollisionDetector.hpp>
#include <Rectangle.hpp>

namespace pjm
{
    bool CollisionDetector::areColliding(const Rectangle& iA, const Rectangle& iB) const
    {
        float leftEdgeA = iA.x;
        float rightEdgeB = iB.x + iB.w;
        if (leftEdgeA > rightEdgeB)
        {
            return false;
        }
        float rightEdgeA = iA.x + iA.w;
        float leftEdgeB = iB.x;
        if (rightEdgeA < leftEdgeB)
        {
            return false;
        }
        float topEdgeA = iA.y;
        float bottomEdgeB = iB.y + iB.h;
        if (topEdgeA > bottomEdgeB)
        {
            return false;
        }
        float bottomEdgeA = iA.y + iA.h;
        float topEdgeB = iB.y;
        if (bottomEdgeA < topEdgeB)
        {
            return false;
        }
        return true;
    }
}
