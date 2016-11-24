#pragma once

#include "ofxStk.h"
#include "ofMain.h"

enum GeneratorType{
    SINE,
    NOISE,
    SQUARE,
    SAW,
    IMPULSE
};

using namespace stk;

// when creating a custom instrument you must subclass stk::Instrmnt
class Synth:public stk::Instrmnt {
public:
    
    Synth();
    
    virtual void noteOn(StkFloat frequency, StkFloat amplitude );
    virtual void noteOff(StkFloat amplitude);
    virtual void setFrequency( StkFloat frequency);
    virtual StkFloat tick( unsigned int channel = 0 );
    virtual StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );
    
    
    void setAttack(float attack){ sineAdsr.setAttackTime(attack); }
    void setDecay(float decay){ sineAdsr.setDecayTime(decay); }
    void setSustain(float sustain){ sineAdsr.setSustainLevel(sustain); }
    void setRelease(float release){ sineAdsr.setReleaseTime(release); }
    
    void setPitchAttack(float attack){ pitchAdsr.setAttackTime(attack); }
    void setPitchDecay(float decay){ pitchAdsr.setDecayTime(decay); }
    void setPitchSustain(float sustain){ pitchAdsr.setSustainLevel(sustain); }
    void setPitchRelease(float release){ pitchAdsr.setReleaseTime(release); }
    void setPitchTarget(float target){ pitchAdsr.setTarget(target); }
    void setPitchBaseFrequency(float freq){ this->baseFrequency = freq; }
    
    void setNoiseAttack(float attack){ noiseAdsr.setAttackTime(attack); }
    void setNoiseDecay(float decay){ noiseAdsr.setDecayTime(decay); }
    void setNoiseSustain(float sustain){ noiseAdsr.setSustainLevel(sustain); }
    void setNoiseRelease(float release){ noiseAdsr.setReleaseTime(release); }
    
    void setLowPassCutoff(float cutoff){ lowPass.setPole(cutoff); }
    void setHighPassCutoff(float cutoff){ highPass.setZero(cutoff); }
    void setGain(float gain){ this->gain = gain; }
    
    void setGeneratorType(GeneratorType type){ this->generatorType = type; }
    
private:
    
    ADSR sineAdsr;
    ADSR pitchAdsr;
    ADSR noiseAdsr;
    
    float gain;
    StkFloat baseFrequency;
    
    stk::SineWave sinewave;
    stk::SineWave sinewaveOctave;
    stk::Noise noise;

    stk::OnePole lowPass;
    stk::OneZero highPass;
    
    GeneratorType generatorType;
    
};
