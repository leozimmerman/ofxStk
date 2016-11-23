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
    
    
    void audioOut(float *output, int bufferSize, int nChannels);
    
    // callback evertime user changes adsr envelope
    void adsrChanged(float &val);
    
    // checks if any keys are being held down;
    bool noNotesDown()const;
    
    
    Synth synth;
    
    
    bool keyDown;
    
    ofxPanel gui;
    ofxFloatSlider attack;
    ofxFloatSlider decay;
    ofxFloatSlider sustain;
    ofxFloatSlider release;
    ofxFloatSlider gain;
    ofxFloatSlider attackTarget;
    ofxFloatSlider sustainLevel;
    ofxIntSlider octave;
    
    ofTrueTypeFont instructions;
    
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
