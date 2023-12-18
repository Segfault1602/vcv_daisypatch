#include "not_daisy_patch.h"

using namespace NotDaisy;

void DaisyPatch::Init(float samplerate)
{
    seed.SetAudioSampleRate(samplerate);

    controls[CTRL_1].Init(&ctrl_vals[CTRL_1], samplerate);
    controls[CTRL_2].Init(&ctrl_vals[CTRL_2], samplerate);
    controls[CTRL_3].Init(&ctrl_vals[CTRL_3], samplerate);
    controls[CTRL_4].Init(&ctrl_vals[CTRL_4], samplerate);

    gate_input[GATE_IN_1].Init(&gate_vals[GATE_IN_1]);
    gate_input[GATE_IN_2].Init(&gate_vals[GATE_IN_2]);

    seed.dac.Init(&cvout_vals[0], &cvout_vals[1]);
}

void DaisyPatch::ProcessAnalogControls()
{
    for (size_t i = 0; i < CTRL_LAST; ++i)
    {
        ctrl_vals[i] = controls[i].Process();
    }
}

void DaisyPatch::ProcessDigitalControls()
{
    // no-op
}

void DaisyPatch::ProcessAllControls()
{
    ProcessAnalogControls();
    ProcessDigitalControls();
}

float DaisyPatch::GetKnobValue(Ctrl k)
{
    return controls[k].Value();
}

void DaisyPatch::SetAudioSampleRate(float sr)
{
    seed.SetAudioSampleRate(sr);
    for (size_t i = 0; i < CTRL_LAST; ++i)
    {
        controls[i].SetSampleRate(sr);
    }
}

float DaisyPatch::AudioSampleRate()
{
    return seed.AudioSampleRate();
}