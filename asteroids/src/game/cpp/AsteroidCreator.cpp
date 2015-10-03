#include <AsteroidCreator.hpp>

using boost::shared_ptr;
using std::list;

namespace pjm
{
    list<shared_ptr<Asteroid> > AsteroidCreator::create(shared_ptr<ScreenWrapper> iScreenWrapper,
                                                        RandomGenerator& iRandomGenerator)
    {
        return list<shared_ptr<Asteroid> >();
    }
}
