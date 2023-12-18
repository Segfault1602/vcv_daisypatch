#include "gatein.h"

using namespace NotDaisy;

void GateIn::Init(float* pin)
{
    pin_ = pin;
    state_ = false;
}

bool GateIn::Trig()
{
    return trigger_.process(*pin_);
}

bool GateIn::State()
{
    state_ = *pin_ > 1.f;
    return state_;
}