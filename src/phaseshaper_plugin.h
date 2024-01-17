#pragma once

#include <cstddef>

#include <daisysp.h>

#include "not_daisy_patch.h"
#include "plugin_impl.h"

using namespace NotDaisy;

class PhaseshaperImpl : public PluginImpl
{
  public:
    PhaseshaperImpl(DaisyPatch& patch) : PluginImpl(patch)
    {
    }
    virtual ~PhaseshaperImpl() override = default;

    /// @brief Initialize the plugin
    /// @param samplerate
    /// This is were you would initialize anything you need to initialize at startup.
    /// Basically, any code that you have in your main() function, before the while(1) loop.
    virtual void Init(size_t samplerate) override;

    /// @brief Audio callback
    /// @param in The input buffers containing the audio input from the 4 inputs
    /// @param out The output buffers containing the audio output for the 4 outputs
    /// @param size The size of the buffers
    virtual void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) override;

    /// @brief Event handler for sample rate changes
    /// @param sr The new sample rate
    virtual void OnSampleRateChange(float sr) override;
};