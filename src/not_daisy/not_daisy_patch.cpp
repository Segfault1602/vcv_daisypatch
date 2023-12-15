#include "not_daisy_patch.h"

using namespace NotDaisy;

void NotDaisyPatch::Init(float samplerate)
{
    seed.SetAudioSampleRate(samplerate);

    controls[CTRL_1].Init(&ctrl_vals[CTRL_1], samplerate);
    controls[CTRL_2].Init(&ctrl_vals[CTRL_2], samplerate);
    controls[CTRL_3].Init(&ctrl_vals[CTRL_3], samplerate);
    controls[CTRL_4].Init(&ctrl_vals[CTRL_4], samplerate);
}

void NotDaisyPatch::ProcessAnalogControls()
{
    // no-op
}

void NotDaisyPatch::ProcessDigitalControls()
{
    // no-op
}

void NotDaisyPatch::ProcessAllControls()
{
    ProcessAnalogControls();
    ProcessDigitalControls();
}

float NotDaisyPatch::GetKnobValue(Ctrl k)
{
    return ctrl_vals[k];
}

void NotDaisyPatch::SetAudioSampleRate(float sr)
{
    seed.SetAudioSampleRate(sr);
    for (size_t i = 0; i < CTRL_LAST; ++i)
    {
        controls[i].SetSampleRate(sr);
    }
}

float NotDaisyPatch::AudioSampleRate()
{
    return seed.AudioSampleRate();
}