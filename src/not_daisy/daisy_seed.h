#pragma once
#ifndef DSY_SEED_H
#define DSY_SEED_H

#include <cstddef>

// Uncomment this out if you're still using the rev2 hardware
// #define SEED_REV2

namespace NotDaisy
{
/**
   @brief This is the higher-level interface for the Daisy board. \n
    All basic peripheral configuration/initialization is setup here. \n

   @ingroup boards
*/
class DaisySeed
{
  public:
    DaisySeed()
    {
    }
    ~DaisySeed()
    {
    }

    /** Updates the Audio Sample Rate, and reinitializes.
     ** Audio must be stopped for this to work.
     */
    void SetAudioSampleRate(float samplerate)
    {
        samplerate_ = samplerate;
    }

    /** Returns the audio sample rate in Hz as a floating point number.
     */
    float AudioSampleRate()
    {
        return samplerate_;
    }

    /** Sets the number of samples processed per channel by the audio callback.
     */
    void SetAudioBlockSize(size_t blocksize)
    {
        blocksize_ = blocksize;
    }

    /** Returns the number of samples per channel in a block of audio. */
    uint32_t AudioBlockSize()
    {
        return blocksize_;
    }

    /** Returns the rate in Hz that the Audio callback is called */
    float AudioCallbackRate() const
    {
        return 0.f;
    }

    DacHandle dac;

  private:
    float samplerate_;
    uint32_t blocksize_;
};

} // namespace NotDaisy

#endif