#pragma once

#define PATCH_INPUT_COUNT (4u)
#define PATCH_OUTPUT_COUNT (4u)

namespace NotDaisy
{
    namespace AudioHandle
    {
        typedef float **OutputBuffer;
        typedef const float *const *InputBuffer;
    }

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
        void ProcessAnalogControls();
        void ProcessAllControls();

        float GetKnobValue(Ctrl k);
        void ProcessDigitalControls();

        float AudioSampleRate();
    };
}