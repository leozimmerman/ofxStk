#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);

    font.loadFont("verdana.ttf", 14);
    
    gui.setup();
    
    gui.add(cutoff.setup("Cutoff",0.0, -0.99, 0.99));
    gui.add(frequency.setup("filter freq HZ", 2000, 0, 22000));
    gui.add(radius.setup("radius",0.0, 0.0, 0.99));

    
    cutoff.addListener(this, &ofApp::filterChanged);
    frequency.addListener(this, &ofApp::filterChanged);
    radius.addListener(this, &ofApp::filterChanged);
    
    beat.setFrequency(0.25);
    
    oneZero.setZero(cutoff);
    onePole.setPole(cutoff);
    twoZero.setNotch(frequency, radius);
    twoPole.setResonance(frequency, radius);
    biquad.setResonance(frequency, radius);
    
    beat.openFile(ofToDataPath("beat.wav",true));
    
    int outChannels = 2;
    int inChannels = 0;
    int samplerate = 44100;
    int bufferSize = 512;
    int nBuffers = outChannels * 2;
    
    stk::Stk::setSampleRate(samplerate);
    ofSoundStreamSetup(outChannels, inChannels, samplerate, bufferSize, nBuffers);
    
    filterType = BIQUAD_RESON;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    
    font.drawString("Press space bar to start and stop audio\nUse the slider to control frequency\nFrequency is measured in file loops per second\n1: One Zero - 2: One Pole - 3: Two Zero\n4: Two Pole - 5: BiQuad Resonant - 6: Biquad Notch", 10, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case ' ':
            shouldPlayAudio = !shouldPlayAudio;
            break;
            
        case '1':
            filterType = ONE_ZERO;
            break;
        case '2':
            filterType = ONE_POLE;
            break;
        case '3':
            filterType = TWO_ZERO;
            break;
        case '4':
            filterType = TWO_POLE;
            break;
        case '5':
            filterType = BIQUAD_RESON;
            break;
        case '6':
            filterType = BIQUAD_NOTCH;
            break;
            
        default:
            break;
    }
    
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    if (shouldPlayAudio) {
        
        stk::StkFrames frames(bufferSize,2);
        beat.tick(frames);
        
        // the beat is a 2 channel file , however most effects only work on on channel
        // so we will just use the left channel. If you want to apply effects on the second channel you need to
        //create two sets of effects one for the left channel and one for the right channel
        stk::StkFrames leftChannel(bufferSize,1);
        // copy the left Channel of 'frames' into `leftChannel`
        frames.getChannel(0, leftChannel, 0);
        
        // applys a filter and writes back into leftChannel
        switch (filterType) {
        
            case ONE_ZERO:
                oneZero.tick(leftChannel);
                break;
            
            case ONE_POLE:
                onePole.tick(leftChannel);
                break;
                
            case TWO_ZERO:
                twoZero.tick(leftChannel);
                break;
                
            case TWO_POLE:
                twoPole.tick(leftChannel);
                break;
                
            case BIQUAD_RESON:
                biquad.tick(leftChannel);
                break;
            
            case BIQUAD_NOTCH:
                biquad.tick(leftChannel);
                break;
                
            default:
                break;
        }
        
        for (int i = 0; i < bufferSize ; i++) {
            output[2*i] = leftChannel(i,0);
            output[2*i+1] = leftChannel(i,0);
        }
    }
}


//--------------------------------------------------------------
void ofApp::filterChanged(float &value){

    oneZero.setZero(cutoff);
    onePole.setPole(cutoff);
    
    twoZero.setNotch(frequency, radius);
    twoPole.setResonance(frequency, radius);
    
    if(filterType == BIQUAD_RESON)
        biquad.setResonance(frequency, radius);
    else
        biquad.setNotch(frequency, radius);
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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




