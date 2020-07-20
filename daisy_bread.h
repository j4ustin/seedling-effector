// # Daisy Bread BSP 
// ## Description 
// Class that handles initializing all of the hardware specific to Justin's breadboard. 
// 
// Helper functions are also in place to provide easy access to build-in control and peripherals. 
// 
// ## Credits 
// **Author:** I mostly ripped off Stephen Hansley 
// **Date Added:** July 2020

#pragma once 
#ifndef DSY_BREAD_BSP_H
#define DSY_BREAD_BSP_H

#include "daisy_seed.h"

namespace daisy
{
class DaisyBread
{
    public:
        enum Sw
        {
            BUTTON_1,
            BUTTON_2,
            BUTTON_LAST,
        };

        enum Knob
        {
            KNOB_1,
            KNOB_2,
            KNOB_3,
            KNOB_LAST,
        };
        DaisyBread();
        ~DaisyBread();

        void Init();
        void DelayMs(size_t del);
        void SetAudioBlockSize(size_t size);
        void StartAudio(dsy_audio_callback cb);
        void ChangeAudioCallback(dsy_audio_callback cb);
        void StartAdc();
        float AudioSampleRate();
        size_t AudioBlockSize();
        float AudioCallbackRate();
        void UpdateAnalogControls();
        float GetKnobValue(Knob k);
        void DebounceControls();
        // TODO: void ClearLeds();
        // TODO: void UpdateLeds();
        DaisySeed seed;
        Encoder encoder;
        AnalogControl knob1, knob2, knob3, *knobs[KNOB_LAST];
        Switch button1, button2, *buttons[BUTTON_LAST];
        // TODO: RgbLed led1, led2;

        private:
            void InitButtons();
            void InitEncoder();
            void InitLeds();
            void InitKnobs();
            float sample_rate_, callback_rate_;
            size_t block_size_;            
};

}

#endif