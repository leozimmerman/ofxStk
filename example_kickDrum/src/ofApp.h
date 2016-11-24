#pragma once

#include "ofMain.h"
#include "ofxStk.h"
#include "ofxGui.h"

#include "Synth.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupGui();
    
    void audioOut(float *output, int bufferSize, int nChannels);
    
    // callback evertime user changes adsr envelope
    void adsrChanged(float &val);
    
    
    
    Synth synth;
    
    
    
    bool keyDown;
    
    ofxPanel gui;
    
    ofParameterGroup adsrParameters;
    ofParameter<float> attack;
    ofParameter<float> decay;
    ofParameter<float> sustain;
    ofParameter<float> release;
    ofParameter<float> gain;
    ofParameter<float> attackTarget;
    
    
    ofParameterGroup pitchEnvParameters;
    ofParameter<float> p_attack;
    ofParameter<float> p_decay;
    ofParameter<float> p_release;
    ofParameter<float> p_target;
    ofParameter<float> p_baseFreq;
    
    ofParameter<float> filterCutoff;
    
    ofTrueTypeFont font;
    
    bool aDown;
    bool sDown;
    bool dDown;
    bool fDown;
    bool gDown;
    bool hDown;
    bool jDown;
    bool kDown;
    bool lDown;
};
