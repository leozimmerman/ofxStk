#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    frequency = 440;
    stk::Stk::setRawwavePath(ofToDataPath("rawwaves",true));
    sine.setFrequency(frequency);
    
    int outChannels = 2;
    int inChannels = 0;
    int samplerate = 44100;
    int bufferSize = 512;
    int nBuffers = outChannels * 2;
    ofSoundStreamSetup(outChannels, inChannels, samplerate, bufferSize, nBuffers);
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    frequency = ( mouseX/(float)ofGetWidth() )  * 800 + 440;
    sine.setFrequency(frequency);
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::blue);
    ofDrawBitmapString(ofToString(frequency), 30, 30);
}
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannnels){
    
    stk::StkFrames sineFrames(bufferSize,1);
    
    sine.tick(sineFrames);
    
    for (int i = 0; i < bufferSize; i++) {
        output[2*i] = sineFrames(i,0);
        output[2*i+1] =  sineFrames(i,0);
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------





