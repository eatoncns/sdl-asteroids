#ifndef _PJM_KEYPRESS_HPP_
#define _PJM_KEYPRESS_HPP_

namespace pjm
{

    struct KeyboardState
    {
        KeyboardState()
            : up(false), left(false), right(false), space(false)
        {}

        bool operator==(const KeyboardState& iOther) const
        {
            return (up == iOther.up &&
                    left == iOther.left &&
                    right == iOther.right &&
                    space == iOther.space);
        }

        bool up;
        bool left;
        bool right;
        bool space;
    };

    namespace keyboard
    {
        enum KeyPress {NONE, UP, LEFT, RIGHT, UP_LEFT, UP_RIGHT};
    }
}

#endif
