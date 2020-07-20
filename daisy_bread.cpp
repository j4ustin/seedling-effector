#include "daisy_bread.h"

#ifndef SAMPLE_RATE
#define SAMPLE_RATE DSY_AUDIO_SAMPLE_RATE
#endif

#define ENC_A_PIN 22
#define ENC_B_PIN 23
#define ENC_CLICK_PIN 13

#define KNOB_1_PIN 24
#define KNOB_2_PIN 25
#define KNOB_3_PIN 26

#define SW_1_PIN 27
#define SW_2_PIN 28

using namespace daisy;

void DaisyBread::Init()
{
    sample_rate_ = SAMPLE_RATE;
    block_size_ = 48; 
    callback_rate_ = (sample_rate_ / static_cast<float>(block_size_));
    seed.Configure();
    seed.Init();
    dsy_tim_start();
    InitButtons();
    InitEncoder();
    // TODO: InitLeds()
    InitKnobs();
    SetAudioBlockSize(block_size_);
}

void DaisyBread::DelayMs(size_t del)
{
    dsy_tim_delay_ms(del);
}

void DaisyBread::StartAudio(dsy_audio_callback cb)
{
    dsy_audio_set_callback(DSY_AUDIO_INTERNAL, cb);
    dsy_audio_start(DSY_AUDIO_INTERNAL);
}

void DaisyBread::ChangeAudioCallback(dsy_audio_callback cb)
{
    dsy_audio_set_callback(DSY_AUDIO_INTERNAL, cb);
}

void DaisyBread::SetAudioBlockSize(size_t size)
{
    block_size_    = size;
    callback_rate_ = (sample_rate_ / static_cast<float>(block_size_));
    dsy_audio_set_blocksize(DSY_AUDIO_INTERNAL, block_size_);
}

float DaisyBread::AudioSampleRate()
{
    return sample_rate_;
}

size_t DaisyBread::AudioBlockSize()
{
    return block_size_;
}

float DaisyBread::AudioCallbackRate()
{
    return callback_rate_;
}

void DaisyBread::StartAdc()
{
    seed.adc.Start();
}

void DaisyBread::UpdateAnalogControls()
{
    knob1.Process();
    knob2.Process();
    knob3.Process();
}

float DaisyBread::GetKnobValue(Knob k)
{
    size_t idx;
    idx = k < KNOB_LAST ? k : KNOB_1;
    return knobs[idx]->Value();
}

void DaisyBread::DebounceControls()
{
    encoder.Debounce();
    button1.Debounce();
    button2.Debounce();
}

void DaisyBread::InitButtons()
{
    // button1
    button1.Init(seed.GetPin(SW_1_PIN), callback_rate_);
    // button2
    button2.Init(seed.GetPin(SW_2_PIN), callback_rate_);

    buttons[BUTTON_1] = &button1;
    buttons[BUTTON_2] = &button2;
}

void DaisyBread::InitEncoder()
{
    dsy_gpio_pin a, b, click;
    a = seed.GetPin(ENC_A_PIN);
    b = seed.GetPin(ENC_B_PIN);
    click = seed.GetPin(ENC_CLICK_PIN);
    encoder.Init(a, b, click, callback_rate_);
}

void DaisyBread::InitKnobs()
{
    // Configure the ADC channels using the desired pin
    AdcChannelConfig knob_init[KNOB_LAST];
    knob_init[KNOB_1].InitSingle(seed.GetPin(KNOB_1_PIN));
    knob_init[KNOB_2].InitSingle(seed.GetPin(KNOB_2_PIN));
    knob_init[KNOB_3].InitSingle(seed.GetPin(KNOB_3_PIN));
    // Initialize with the knob init struct w/ 2 members
    // Set Oversampling to 32x
    seed.adc.Init(knob_init, KNOB_LAST);
    // Make an array of pointers to the knobs.
    knobs[KNOB_1] = &knob1;
    knobs[KNOB_2] = &knob2;
    knobs[KNOB_3] = &knob3;
    for(int i = 0; i < KNOB_LAST; i++)
    {
        knobs[i]->Init(seed.adc.GetPtr(i), callback_rate_);
    }
}

/* TODO: Add LEDs
void DaisyBread::ClearLeds()
{
    // Using Color
    Color c;
    c.Init(Color::PresetColor::OFF);
    led1.SetColor(c);
    led2.SetColor(c);
    // Without
    // led1.Set(0.0f, 0.0f, 0.0f);
    // led2.Set(0.0f, 0.0f, 0.0f);
}

void DaisyBread::UpdateLeds()
{
    led1.Update();
    led2.Update();
}

void DaisyBread::InitLeds()
{
    // LEDs are just going to be on/off for now.
    // TODO: Add PWM support
    dsy_gpio_pin rpin, gpin, bpin;

    rpin = seed.GetPin(LED_1_R_PIN);
    gpin = seed.GetPin(LED_1_G_PIN);
    bpin = seed.GetPin(LED_1_B_PIN);
    led1.Init(rpin, gpin, bpin, true);

    rpin = seed.GetPin(LED_2_R_PIN);
    gpin = seed.GetPin(LED_2_G_PIN);
    bpin = seed.GetPin(LED_2_B_PIN);
    led2.Init(rpin, gpin, bpin, true);

    ClearLeds();
    UpdateLeds();
}
*/