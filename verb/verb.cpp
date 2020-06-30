#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hardware;
ReverbSc verb;

// use the button to activate the verb
Switch button1;

int main(void)
{
    // configure and initialize the seed
    hardware.Configure();
    hardware.Init();

    // fetch sample per second
    float samplerate = hardware.AudioSampleRate();

    // create adc configuration  
    AdcChannelConfig adcConfig;
    // add stereo input channels (16,17)
}