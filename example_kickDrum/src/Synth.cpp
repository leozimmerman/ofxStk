#include "Synth.h"

Synth::Synth(){
    
    stk::Stk::setRawwavePath(ofToDataPath("rawwaves",true));
    setFrequency(440.0);
    
    generatorType = SINE;
    filter.setPole(0.0);
    
}

void Synth::noteOn(StkFloat frequency, StkFloat amplitude){
    
    adsr.keyOn();
    
    setFrequency(frequency);
    gain = amplitude;
    
    pitchAdsr.keyOn();
    
}

void Synth::noteOff(StkFloat amplitude){

    adsr.keyOff();
    pitchAdsr.keyOff();
    
}
void Synth::setFrequency(StkFloat frequency){
    
    sinewave.setFrequency(frequency);
    
}


// inside tick you are responsible for setting lastFrame_
StkFloat Synth::tick(unsigned int channel){
    
    if (pitchAdsr.tick() > 0.0){
        setFrequency(pitchAdsr.tick() * baseFrequency);
    }
    
    lastFrame_[0] = sinewave.tick();
    lastFrame_[0] *= adsr.tick();
    lastFrame_[0] *= gain;
    
    lastFrame_[0] = filter.tick(lastFrame_[0]);
    
    return lastFrame_[0];
    
}

StkFrames& Synth::tick(StkFrames &frames,unsigned int channel){
   
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = tick();
    return frames;
    
}

