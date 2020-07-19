#include "daisy_bread.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

static DaisyBread hardware;
static ReverbSc verb;

float currentDelay, feedback, delayTarget, cutoff; 

// use the button to activate the verb
Switch button1;

void Controls();

void AudioCallback(float *in, float *out, size_t size) 
{
    float outl, outr, inl, inr; 

    Controls();

    for (size_t i = 0; i < size; i += 2) 
    {   
        // fetch the incoming sample
        inl = in[i];
        inr = in[i + 1];

        verb.Process(inl, inr, &outl, &outr);        
        
        // output samples 
        out[i] = outl;
        out[i + 1] = outr;
    }
}

int main(void)
{
    // configure and initialize the seed
    hardware.Configure();
    hardware.Init();

    // fetch sample per second
    float samplerate = hardware.AudioSampleRate();

    // add knob controls
    AdcChannelConfig adcConfig;
    adcConfig.InitSingle(hardware.GetPin(21));
    adcConfig.InitSingle(hardware.GetPin(22));
}

void Controls() 
{
    float k1, k2, k3, k4;
    delayTarget = feedbac = drywet = 0;
    
    
}