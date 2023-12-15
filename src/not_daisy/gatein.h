#pragma once
#ifndef DSY_GATEIN_H
#define DSY_GATEIN_H

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
    GateIn()
    {
    }

    /** GateIn Destructor */
    ~GateIn()
    {
    }

    /** Checks current state of gate input.
     *  @return True if the GPIO just transitioned.
     */
    bool Trig();

    /** Checks current state of gate input (no state required)
     */
    inline bool State()
    {
        return state_;
    }

  private:
    bool prev_state_, state_;
};
} // namespace NotDaisy
#endif