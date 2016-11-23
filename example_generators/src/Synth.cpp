#include "Synth.h"

Synth::Synth(){
    
    index = 0.0;
    stk::Stk::setRawwavePath(ofToDataPath("rawwaves",true));
    setFrequency(440.0);
    
    generatorType = SQUARE;
}

void Synth::noteOn(StkFloat frequency, StkFloat amplitude){
    
    adsr.keyOn();
    setFrequency(frequency);
    gain = amplitude;
    
}

void Synth::noteOff(StkFloat amplitude){
    adsr.keyOff();
}

void Synth::setFrequency(StkFloat newFreq){
    
    frequency = newFreq;
    sinewave.setFrequency(frequency);
    square.setFrequency(frequency);
    saw.setFrequency(frequency);
    impulseTrain.setFrequency(frequency);
    
}

// inside tick you are responsible for setting lastFrame_
StkFloat Synth::tick(unsigned int channel){
    
    switch (generatorType) {
    
        case SINE:
            lastFrame_[0] = sinewave.tick();
            break;
        case NOISE:
            lastFrame_[0] = noise.tick();
            break;
        case SQUARE:
            lastFrame_[0] = square.tick();
            break;
        case SAW:
            lastFrame_[0] = saw.tick();
            break;
        case IMPULSE:
            lastFrame_[0] = impulseTrain.tick();
            break;
            
        default:
            lastFrame_[0] = 0.0;
            break;
            
    }
    
    
    
    lastFrame_[0] *= adsr.tick();
    lastFrame_[0] *= gain;
    return lastFrame_[0];
    
}

StkFrames& Synth::tick(StkFrames &frames,unsigned int channel){
   
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = tick();
    return frames;
    
}

