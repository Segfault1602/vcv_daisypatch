#pragma once
#ifndef DSY_ENCODER_H
#define DSY_ENCODER_H

#include <cstdint>

namespace NotDaisy
{
    /**
        @brief Generic Class for handling Quadrature Encoders \n
        Inspired/influenced by Mutable Instruments (pichenettes) Encoder classes
        @author Stephen Hensley
        @date December 2019
        @ingroup controls
    */
    class Encoder
    {
    public:
        Encoder() {}
        ~Encoder() {}

        /** Initializes the encoder with the specified hardware pins.
         * Update rate is to be deprecated in a future release
         */
        void Init();
        /** Called at update_rate to debounce and handle timing for the switch.
         * In order for events not to be missed, its important that the Edge/Pressed checks be made at the same rate as the debounce function is being called.
         */
        void Debounce();

        /** Returns +1 if the encoder was turned clockwise, -1 if it was turned counter-clockwise, or 0 if it was not just turned. */
        inline int32_t Increment() const { return updated_ ? inc_ : 0; }

        /** Returns true if the encoder was just pressed. UNIMPLEMENTED */
        inline bool RisingEdge() const { return false; }

        /** Returns true if the encoder was just released. UNIMPLEMENTED */
        inline bool FallingEdge() const { return false; }

        /** Returns true while the encoder is held down. UNIMPLEMENTED*/
        inline bool Pressed() const { return false; }

        /** Returns the time in milliseconds that the encoder has been held down. UNIMPLEMENTED */
        inline float TimeHeldMs() const { return 0; }

        /** To be removed in breaking update
         * \param update_rate Does nothing
         */
        inline void SetUpdateRate(float update_rate) {}

    private:
        uint32_t last_update_;
        bool updated_;
        int32_t inc_;
    };
} // namespace daisy
#endif