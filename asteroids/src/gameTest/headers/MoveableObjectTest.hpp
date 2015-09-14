#ifndef _PJM_MOVEABLEOBJECTTEST_HPP_
#define _PJM_MOVEABLEOBJECTTEST_HPP_

#include <Vector.hpp>
#include <TestRenderable.hpp>
#include <TestImageLoader.hpp>
#include <TestScreenWrapper.hpp>

class MoveableObjectTest : public ::testing::Test
{
    protected:
        MoveableObjectTest()
            : _initialLocation(100, 100),
              _wrapper(pjm::Vector(200, 200))
        {
            _imageLoader.renderable = &_testRenderable;
        }
        
        pjm::Vector _initialLocation;
        ::testing::NiceMock<TestScreenWrapper> _wrapper;
        TestImageLoader _imageLoader;
        TestRenderable _testRenderable;
};

#endif
