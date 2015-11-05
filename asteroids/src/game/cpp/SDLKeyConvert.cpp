#include <SDLKeyConvert.hpp>
#include <map>
#include <boost/assign/list_of.hpp>

using boost::assign::map_list_of;

namespace pjm
{
    typedef std::map<std::string, keyboard::KeyPress> key_map_t;
                                        //ULR
    const key_map_t keyMap = map_list_of("100", keyboard::UP)
                                        ("111", keyboard::UP)
                                        ("010", keyboard::LEFT)
                                        ("001", keyboard::RIGHT)
                                        ("110", keyboard::UP_LEFT)
                                        ("101", keyboard::UP_RIGHT);

    void encodeLookup(std::string& iLookup, const Uint8* iState, const Uint8 iCode)
    {
        iState[iCode] ? iLookup.append("1") : iLookup.append("0");
    }

    keyboard::KeyPress SDLKeyConvert(const Uint8* iState)
    {
        std::string lookup;
        encodeLookup(lookup, iState, SDL_SCANCODE_UP);
        encodeLookup(lookup, iState, SDL_SCANCODE_LEFT);
        encodeLookup(lookup, iState, SDL_SCANCODE_RIGHT);
        key_map_t::const_iterator it = keyMap.find(lookup);
        if (it != keyMap.end())
        {
            return it->second;
        }
        return keyboard::NONE;
    }
}
