#include "gatein.h"

using namespace NotDaisy;

bool GateIn::Trig()
{
    bool trigger = state_ && !prev_state_;
    prev_state_ = state_;
    return trigger;
}