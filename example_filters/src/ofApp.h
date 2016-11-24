#pragma once

#include "ofMain.h"
#include "ofxStk.h"
#include "ofxGui.h"

enum FilterType{
    ONE_ZERO,
    ONE_POLE,
    TWO_ZERO,
    TWO_POLE,
    BIQUAD_RESON,
    BIQUAD_NOTCH,
};

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
    
    void audioOut(float *output,int bufferSize,int nChannels);
    void chorusParametersChanged(float &value);
    void reverbParametersChanged(float &value);

    void filterChanged(float &value);
    
    ofxPanel gui;

    ofxFloatSlider cutoff;
    ofxFloatSlider frequency;
    ofxFloatSlider radius;
    
    stk::FileLoop beat;
    
    stk::OneZero oneZero;//highPass working only
    stk::OnePole onePole;//highPass LowPass
    stk::TwoZero twoZero;//notch
    stk::TwoPole twoPole;//resonator
    stk::BiQuad  biquad;
    
    
    
    ofTrueTypeFont font;
    bool shouldPlayAudio;
    
    FilterType filterType;
};
