#include <RandomGeneratorImpl.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <ctime>

using namespace boost::random;

namespace pjm
{
    static mt19937 gen(std::time(0));

    float RandomGeneratorImpl::uniformAboutZero(float iRange)
    {
        uniform_real_distribution<float> dist(0.0, 2*iRange);
        float temp = dist(gen);
        return (temp - iRange);
    }

}
