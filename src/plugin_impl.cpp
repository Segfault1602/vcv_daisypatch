#include "plugin_impl.h"

#include "gpio.h"
#include <daisysp.h>
#include <rack.hpp>

#include <cmath>

using namespace daisysp;

#define TWO_PI (2.f * 3.1415926535f)

void PluginImpl::Init(size_t samplerate)
{
    // This is were you would initialize anything you need to initialize at startup.
    // Basically, any code that you have in your main() function, before the while(1) loop.
    patch_.Init(samplerate);
}

void PluginImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    // Your code here
}

void PluginImpl::OnSampleRateChange(float sr)
{
    // As opposed to the Daisy platform, samplerate is set by the user and not at compile time.
    // Add code here to handle samplerate changes. Or don't.
}