#ifndef _PJM_KEYPRESS_HPP_
#define _PJM_KEYPRESS_HPP_

namespace pjm
{

    struct ShipAction
    {
        ShipAction()
            : accelerate(false), turn_left(false), turn_right(false), shoot(false)
        {}

        bool operator==(const ShipAction& iOther) const
        {
            return (accelerate == iOther.accelerate &&
                    turn_left == iOther.turn_left &&
                    turn_right == iOther.turn_right &&
                    shoot == iOther.shoot);
        }

        bool accelerate;
        bool turn_left;
        bool turn_right;
        bool shoot;
    };

    namespace keyboard
    {
        enum KeyPress {NONE, UP, LEFT, RIGHT, UP_LEFT, UP_RIGHT};
    }
}

#endif
