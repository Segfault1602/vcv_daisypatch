#pragma once
#ifndef DSY_GATEIN_H
#define DSY_GATEIN_H

#include <rack.hpp>

namespace NotDaisy
{
/**
   @brief Generic Class for handling gate inputs through GPIO.
   @author Stephen Hensley
   @date    March 2020
   @ingroup controls
*/
class GateIn
{
  public:
    /** GateIn Constructor */
    GateIn() = default;

    void Init(float* pin);

    /** Checks current state of gate input.
     *  @return True if the GPIO just transitioned.
     */
    bool Trig();

    /** Checks current state of gate input (no state required)
     */
    bool State();

  private:
    float* pin_ = nullptr;
    bool state_ = false;

    rack::dsp::SchmittTrigger trigger_;
};
} // namespace NotDaisy
#endif