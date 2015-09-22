#include <RandomGeneratorImpl.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <ctime>

using namespace boost::random;

namespace pjm
{
    static mt19937 gen(std::time(0));

    float RandomGeneratorImpl::uniformInRange(float iMin, float iMax)
    {
        uniform_real_distribution<float> dist(iMin, iMax);
        return dist(gen);
    }

}
