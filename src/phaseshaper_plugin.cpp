#include "phaseshaper_plugin.h"

#include "gpio.h"
// #include <daisysp.h>
#include <dsp_utils.h>
#include <filter.h>
#include <phaseshapers.h>
#include <rack.hpp>

#include <cmath>

using namespace daisysp;

static sfdsp::Phaseshaper osc_;
static sfdsp::Biquad m_outputFilter;

void PhaseshaperImpl::Init(size_t samplerate)
{
    // This is were you would initialize anything you need to initialize at startup.
    // Basically, any code that you have in your main() function, before the while(1) loop.
    patch_.Init(samplerate);
    osc_.Init(samplerate);
    osc_.SetWaveform(sfdsp::Phaseshaper::Waveform::WAVESLICE);

    m_outputFilter.SetCoefficients(0.29289322, 0.58578644, 0.29289322, 0, -0.171572875);
}

void PhaseshaperImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    patch_.ProcessAllControls();
    const float kBaseNote = rack::dsp::FREQ_C4;
    const float cv = patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_1) - 2.5f;
    const float f = kBaseNote * std::pow(2.f, cv);
    osc_.SetFreq(f);

    const float d_cv = (patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_2) / 5.f);
    const float waveform_cv = (patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_3) / 5.f) *
                              static_cast<float>(sfdsp::Phaseshaper::Waveform::NUM_WAVES);

    osc_.SetMod(d_cv);
    osc_.SetWaveform(static_cast<sfdsp::Phaseshaper::Waveform>(waveform_cv));

    osc_.ProcessBlock(out[0], size);
    m_outputFilter.ProcessBlock(out[0], out[1], size);
}

void PhaseshaperImpl::OnSampleRateChange(float sr)
{
    // As opposed to the Daisy platform, samplerate is set by the user and not at compile time.
    // Add code here to handle samplerate changes. Or don't.
    osc_.Init(sr);
}