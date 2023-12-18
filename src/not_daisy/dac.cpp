#include "dac.h"

using namespace NotDaisy;

float* DacHandle::cv1_ = nullptr;
float* DacHandle::cv2_ = nullptr;

void DacHandle::Init(float* cv1, float* cv2)
{
    DacHandle::cv1_ = cv1;
    DacHandle::cv2_ = cv2;
}

DacHandle::Result DacHandle::WriteValue(Channel chn, uint16_t val)
{
    // The DAC on daisy are 12-bit, so scale the value to that range.
    constexpr uint16_t kMaxVal = 4095;

    // Scale to 0.0f - 1.0f
    float scaled_val = static_cast<float>(val) / static_cast<float>(kMaxVal);
    scaled_val *= 5.0f; // Scale to 0.0f - 5.0f
    if (chn == Channel::ONE)
    {
        *cv1_ = scaled_val;
    }
    else if (chn == Channel::TWO)
    {
        *cv2_ = scaled_val;
    }
    else if (chn == Channel::BOTH)
    {
        *cv1_ = scaled_val;
        *cv2_ = scaled_val;
    }
    return Result::OK;
}