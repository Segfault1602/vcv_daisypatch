#pragma once
#ifndef DSY_DAC_H
#define DSY_DAC_H

#include <cstdint>

namespace NotDaisy
{
/** @brief DAC handle for Built-in DAC Peripheral
 *  @ingroup per_analog
 **
 ** For now only Normal Mode is supported,
 ** Sample and hold mode provides reduced power consumption, but requires a bit more setup.
 **
 ** For now connecting the DAC through other internal peripherals is also not supported.
 **
 ** Since the DAC channels have dedicated pins we don't need to pass in a pin config like with
 ** other modules. However, it is still important to not try to use the DAC pins for anything else.
 ** DAC Channel 1 is on PA4, and DAC Channel 2 is on PA5
 ***/
class DacHandle
{
  public:
    /** Return Values for the DacHandle class */
    enum class Result
    {
        OK,
        ERR,
    };

    /** Selects which channel(s) will be configured for use. */
    enum class Channel
    {
        ONE,
        TWO,
        BOTH,
    };

    static void Init(float* cv1, float* cv2);

    Result WriteValue(Channel chn, uint16_t val);

  private:
    static float* cv1_;
    static float* cv2_;
};
} // namespace NotDaisy

#endif