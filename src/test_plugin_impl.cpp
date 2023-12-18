#include "test_plugin_impl.h"

#include <daisysp.h>

using namespace NotDaisy;
using namespace daisysp;

void TestPluginImpl::Init(size_t samplerate)
{
    // This is were you would initialize anything you need to initialize at startup.
    // Basically, any code that you have in your main() function, before the while(1) loop.
    patch_.Init(samplerate);

    for (size_t i = 0; i < kNumOscs; ++i)
    {
        osc_[i].Init(samplerate);
        osc_[i].SetWaveform(Oscillator::WAVE_SIN + i);
    }
}

void TestPluginImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    // Simple example of a quad sine oscillator using the 4 cv inputs as v/oct inputs.
    patch_.ProcessAllControls();

    const float kBaseNote = rack::dsp::FREQ_C4;

    for (int i = 0; i < patch_.CTRL_LAST; ++i)
    {
        const float cv = patch_.GetKnobValue(static_cast<DaisyPatch::Ctrl>(i));
        const float f = kBaseNote * std::pow(2.f, cv);
        osc_[i].SetFreq(f);
    }

    for (size_t i = 0; i < size; ++i)
    {
        out[0][i] = osc_[0].Process();
        out[1][i] = osc_[1].Process();
        out[2][i] = osc_[2].Process();
        out[3][i] = osc_[3].Process();
    }

    // Logical OR of the two gate inputs
    if (patch_.gate_input[0].State() || patch_.gate_input[1].State())
    {
        dsy_gpio_write(&patch_.gate_output, true);
    }
    else
    {
        dsy_gpio_write(&patch_.gate_output, false);
    }

    // Comparator for cv outs
    float cv_1 = patch_.controls[patch_.CTRL_1].Value();
    float cv_2 = patch_.controls[patch_.CTRL_2].Value();
    float cv_out1 = fmaxf(cv_1, cv_2);
    float cv_out2 = fminf(cv_1, cv_2);

    // Scale to 12 bits uint16_t
    uint16_t cv_out1_scaled = static_cast<uint16_t>(cv_out1 / 5.f * 4095.f);
    uint16_t cv_out2_scaled = static_cast<uint16_t>(cv_out2 / 5.f * 4095.f);

    patch_.seed.dac.WriteValue(DacHandle::Channel::ONE, cv_out1_scaled);
    patch_.seed.dac.WriteValue(DacHandle::Channel::TWO, cv_out2_scaled);
}

void TestPluginImpl::OnSampleRateChange(float sr)
{
    for (size_t i = 0; i < kNumOscs; ++i)
    {
        osc_[i].Init(sr);
        osc_[i].SetWaveform(Oscillator::WAVE_SIN + i);
    }
}
