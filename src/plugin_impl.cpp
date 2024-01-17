#include "plugin_impl.h"

#include "gpio.h"
// #include <daisysp.h>
#include <dsp_utils.h>
#include <rack.hpp>
#include <vector_phaseshaper.h>

#include <cmath>

using namespace daisysp;

static sfdsp::VectorPhaseshaper osc_;

void PluginImpl::Init(size_t samplerate)
{
    // This is were you would initialize anything you need to initialize at startup.
    // Basically, any code that you have in your main() function, before the while(1) loop.
    patch_.Init(samplerate);
    osc_.Init(samplerate);
    osc_.SetMod(0.05f, 0.5f);
    osc_.SetFormantMode(sfdsp::VectorPhaseshaper::FormantMode::RATIO);
}

void PluginImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    patch_.ProcessAllControls();
    const float kBaseNote = rack::dsp::FREQ_C4;
    const float cv = patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_1) - 2.5f;
    const float f = kBaseNote * std::pow(2.f, cv);
    osc_.SetFreq(f);

    const float d_cv = (patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_2) / 5.f);
    const float v_cv = (patch_.GetKnobValue(DaisyPatch::Ctrl::CTRL_3));

    osc_.SetMod(d_cv, v_cv);

    osc_.ProcessBlock(out[0], size);
}

void PluginImpl::OnSampleRateChange(float sr)
{
    // As opposed to the Daisy platform, samplerate is set by the user and not at compile time.
    // Add code here to handle samplerate changes. Or don't.
}