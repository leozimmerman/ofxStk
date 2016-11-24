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

    
    ofxPanel gui;
    
    ofParameterGroup sineAdsrParameters;
    ofParameter<float> attack;
    ofParameter<float> decay;
    ofParameter<float> sustain;
    ofParameter<float> release;
    
    ofParameterGroup pitchAdsrParameters;
    ofParameter<float> p_attack;
    ofParameter<float> p_decay;
    ofParameter<float> p_release;
    ofParameter<float> p_target;
    ofParameter<float> p_baseFreq;
    
    ofParameterGroup noiseAdsrParameters;
    ofParameter<float> n_attack;
    ofParameter<float> n_decay;
    ofParameter<float> n_release;
    ofParameter<float> n_sustain;
    
    
    ofParameter<float> lowPassCutoff;
    ofParameter<float> highPassPassCutoff;
    ofParameter<float> gain;
    
    ofTrueTypeFont font;

};
