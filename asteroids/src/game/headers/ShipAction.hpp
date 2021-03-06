#ifndef _PJM_SHIPACTION_HPP_
#define _PJM_SHIPACTION_HPP_

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

        bool operator!=(const ShipAction& iOther) const
        {
            return !(*this == iOther);
        }

        ShipAction& accelerating()
        {
            accelerate = true;
            return *this;
        }

        ShipAction& turningLeft()
        {
            turn_left = true;
            return *this;
        }

        ShipAction& turningRight()
        {
            turn_right = true;
            return *this;
        }

        ShipAction& shooting()
        {
            shoot = true;
            return *this;
        }

        bool accelerate;
        bool turn_left;
        bool turn_right;
        bool shoot;
    };
}

#endif
