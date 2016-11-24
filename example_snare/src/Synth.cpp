#include "Synth.h"

Synth::Synth(){
    
    stk::Stk::setRawwavePath(ofToDataPath("rawwaves",true));
    setFrequency(440.0);
    
    generatorType = SINE;
    lowPass.setPole(0.0);
    highPass.setZero(0.0);
    
}

void Synth::noteOn(StkFloat frequency, StkFloat amplitude){
    
    setFrequency(frequency);
    //gain = amplitude;
    sineAdsr.keyOn();
    pitchAdsr.keyOn();
    noiseAdsr.keyOn();
    
}

void Synth::noteOff(StkFloat amplitude){

    sineAdsr.keyOff();
    pitchAdsr.keyOff();
    
    noiseAdsr.keyOff();
    
}
void Synth::setFrequency(StkFloat frequency){
    
    sinewave.setFrequency(frequency);
    sinewaveOctave.setFrequency(frequency*2);
    
}

//Inside tick you are responsible for setting lastFrame_
StkFloat Synth::tick(unsigned int channel){
    
    //Sine
    StkFloat sineFrame;
    StkFloat noiseFrame;
    
    if (pitchAdsr.tick() > 0.0){
        setFrequency(pitchAdsr.tick() * baseFrequency);
    }
    
    sineFrame = sinewave.tick() + sinewaveOctave.tick();
    sineFrame *= 0.5;
    
    sineFrame *= sineAdsr.tick();
    sineFrame = lowPass.tick(sineFrame);
    
    //Noise
    noiseFrame = noise.tick();
    noiseFrame *= noiseAdsr.tick();
    noiseFrame = highPass.tick(noiseFrame);

    //Mix
    lastFrame_[0] = sineFrame*gain + noiseFrame*(1-gain);
    
    return lastFrame_[0];
    
}

StkFrames& Synth::tick(StkFrames &frames,unsigned int channel){
   
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = tick();
    return frames;
    
}

