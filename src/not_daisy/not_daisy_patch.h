#pragma once

#include "ctrl.h"
#include "dac.h"
#include "daisy_seed.h"
#include "encoder.h"
#include "gatein.h"
#include "gpio.h"

#define PATCH_INPUT_COUNT (4u)
#define PATCH_OUTPUT_COUNT (4u)
#define PATCH_GATE_INPUT_COUNT (2u)

namespace NotDaisy
{
namespace AudioHandle
{
typedef float** OutputBuffer;
typedef const float* const* InputBuffer;
} // namespace AudioHandle

class DaisyPatch
{
  public:
    enum Ctrl
    {
        CTRL_1,
        CTRL_2,
        CTRL_3,
        CTRL_4,
        CTRL_LAST,
    };

    enum GateInput
    {
        GATE_IN_1,
        GATE_IN_2,
        GATE_IN_LAST,
    };

    DaisyPatch() = default;

    void Init(float samplerate);
    void ProcessAnalogControls();
    void ProcessDigitalControls();
    void ProcessAllControls();

    float GetKnobValue(Ctrl k);

    void SetAudioSampleRate(float sr);
    float AudioSampleRate();

    DaisySeed seed;                    /**< Seed object */
    Encoder encoder;                   /**< Encoder object */
    AnalogControl controls[CTRL_LAST]; /**< Array of controls*/
    GateIn gate_input[GATE_IN_LAST];   /**< Gate inputs  */
    dsy_gpio gate_output;

    // Hardware
    float ctrl_vals[CTRL_LAST];
    float gate_vals[GATE_IN_LAST];
    float cvout_vals[2];
};
} // namespace NotDaisy