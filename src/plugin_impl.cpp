#include "plugin_impl.h"

void PluginImpl::AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        out[0][i] = in[0][i] * -1.f;
        out[1][i] = in[1][i] * -1.f;
        out[2][i] = in[2][i] * -1.f;
        out[3][i] = in[3][i] * -1.f;
    }
}