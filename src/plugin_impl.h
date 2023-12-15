#pragma once

#include <cstddef>

#include "not_daisy_patch.h"

using namespace NotDaisy;

class PluginImpl
{
public:
    PluginImpl() = default;

    void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size);
};