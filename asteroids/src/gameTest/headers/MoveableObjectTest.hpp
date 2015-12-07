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
              _wrapper(new ::testing::NiceMock<TestScreenWrapper>(pjm::Vector(200, 200))),
              _testRenderable(new TestRenderable())
        {
            _imageLoader.renderable = _testRenderable;
        }

        template <typename T>
        void expectObjectToRenderAt(T& iObject,
                                    const pjm::Vector& iLocation,
                                    const double iAngle)
        {
            iObject.render();
            ASSERT_FALSE(_testRenderable->renderCalls.empty());
            EXPECT_THAT(_testRenderable->renderCalls.back(),
                        ::testing::Pair(iLocation, iAngle));
        }

        template <typename T>
        void expectObjectToRenderAtAngle(T& iObject, const double iAngle)
        {
            iObject.render();
            ASSERT_FALSE(_testRenderable->renderCalls.empty());
            EXPECT_THAT(_testRenderable->renderCalls.back(),
                        ::testing::Pair(::testing::_, iAngle));
        }

        template <typename T>
        void expectObjectToRenderAtLocation(T& iObject, const pjm::Vector& iLocation)
        {
            iObject.render();
            ASSERT_FALSE(_testRenderable->renderCalls.empty());
            EXPECT_THAT(_testRenderable->renderCalls.back(),
                        ::testing::Pair(iLocation, ::testing::_));
        }

        pjm::Vector _initialLocation;
        boost::shared_ptr< ::testing::NiceMock<TestScreenWrapper> > _wrapper;
        TestImageLoader _imageLoader;
        boost::shared_ptr<TestRenderable> _testRenderable;
};

#endif
