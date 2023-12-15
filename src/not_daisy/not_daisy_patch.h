#pragma once

#include "ctrl.h"
#include "daisy_seed.h"
#include "encoder.h"
#include "gatein.h"

#define PATCH_INPUT_COUNT (4u)
#define PATCH_OUTPUT_COUNT (4u)

namespace NotDaisy
{
namespace AudioHandle
{
typedef float** OutputBuffer;
typedef const float* const* InputBuffer;
} // namespace AudioHandle

class NotDaisyPatch
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

    NotDaisyPatch() = default;

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

    // Hardware
    float ctrl_vals[CTRL_LAST];
};
} // namespace NotDaisy