#include "plugin_impl.h"

#include <rack.hpp>

#include <cmath>

#define TWO_PI (2.f * 3.1415926535f)

void PluginImpl::Init(size_t samplerate)
{
    // This is were you would initialize anything you need to initialize at startup.
    // Basically, any code that you have in your main() function, before the while(1) loop.
    patch_.Init(samplerate);
}

void PluginImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    // Simple example of a quad sine oscillator using the 4 cv inputs as v/oct inputs.
    patch_.ProcessAllControls();

    const float kBaseNote = rack::dsp::FREQ_C4;

    const float cv1 = patch_.controls[patch_.CTRL_1].Process();
    const float cv2 = patch_.controls[patch_.CTRL_2].Process();
    const float cv3 = patch_.controls[patch_.CTRL_3].Process();
    const float cv4 = patch_.controls[patch_.CTRL_4].Process();

    const float f1 = kBaseNote * std::pow(2.f, cv1);
    const float f2 = kBaseNote * std::pow(2.f, cv2);
    const float f3 = kBaseNote * std::pow(2.f, cv3);
    const float f4 = kBaseNote * std::pow(2.f, cv4);

    const float samplerate = patch_.AudioSampleRate();

    const float p1_inc = f1 / samplerate;
    const float p2_inc = f2 / samplerate;
    const float p3_inc = f3 / samplerate;
    const float p4_inc = f4 / samplerate;

    p1 += p1_inc;
    p1 = std::fmod(p1, 1.f);
    p2 += p2_inc;
    p2 = std::fmod(p2, 1.f);
    p3 += p3_inc;
    p3 = std::fmod(p3, 1.f);
    p4 += p4_inc;
    p4 = std::fmod(p4, 1.f);

    for (size_t i = 0; i < size; ++i)
    {
        out[0][i] = std::sin(p1 * TWO_PI);
        out[1][i] = std::sin(p2 * TWO_PI);
        out[2][i] = std::sin(p3 * TWO_PI);
        out[3][i] = std::sin(p4 * TWO_PI);
    }
}

void PluginImpl::OnSampleRateChange(float sr)
{
    // As opposed to the Daisy platform, samplerate is set by the user and not at compile time.
    // Add code here to handle samplerate changes. Or don't.
}