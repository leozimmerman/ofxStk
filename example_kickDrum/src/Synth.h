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
    
    
    void setAttack(float attack){ adsr.setAttackTime(attack); }
    void setDecay(float decay){ adsr.setDecayTime(decay); }
    void setSustain(float sustain){ adsr.setSustainLevel(sustain); }
    void setRelease(float release){ adsr.setReleaseTime(release); }
    void setGain(float gain){ this->gain = gain; }
    void setAttackTarget(float target){ adsr.setAttackTarget(target); }
    
    
    void setPitchAttack(float attack){ pitchAdsr.setAttackTime(attack); }
    void setPitchDecay(float decay){ pitchAdsr.setDecayTime(decay); }
    void setPitchSustain(float sustain){ pitchAdsr.setSustainLevel(sustain); }
    void setPitchRelease(float release){ pitchAdsr.setReleaseTime(release); }
    void setPitchTarget(float target){ pitchAdsr.setTarget(target); }
    void setPitchBaseFrequency(float freq){ this->baseFrequency = freq; }
    
    void setFilterCutoff(float cutoff){ filter.setPole(cutoff); }
    
    void setGeneratorType(GeneratorType type){ this->generatorType = type; }
    
private:
    
    //StkFloat frequency;
    ADSR adsr;
    ADSR pitchAdsr;
    
    float gain;
    StkFloat baseFrequency;
    
    stk::SineWave sinewave;

    stk::OnePole filter;
    
    GeneratorType generatorType;
    
};
