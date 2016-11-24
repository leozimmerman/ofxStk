#include "ofApp.h"

using namespace stk;

const float NoteC = 65.41;
const float NoteD = 73.42;
const float NoteE = 82.41;
const float NoteF = 87.31;
const float NoteG = 98.0;
const float NoteA = 110.0;
const float NoteB = 123.47;
const float NoteC2 = 130.81;
const float NoteD2 = 146.83;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);
    
    font.loadFont("verdana.ttf", 14);
    
    setupGui();
    
    
    synth.setAttack(attack/1000.0);
    synth.setDecay(decay/1000.0);
    synth.setSustain(sustain);
    synth.setRelease(release/1000.0);
    synth.setGain(gain);
    synth.setAttackTarget(attackTarget);
    
    synth.setPitchAttack(p_attack/1000.0);
    synth.setPitchDecay(p_decay/1000.0);
    synth.setPitchRelease(p_release/1000.0);
    synth.setPitchTarget(p_target);
    synth.setPitchBaseFrequency(p_baseFreq);
    
    
    int outChannels = 2;
    int inChannels = 0;
    int samplerate = 44100;
    int bufferSize = 512;
    int nBuffers = outChannels * 2;
    
    stk::Stk::setSampleRate(samplerate);
    ofSoundStreamSetup(outChannels, inChannels, samplerate, bufferSize, nBuffers);
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    font.drawString("Press spacebar to play sound", 10, 350);
    
    font.drawString("Base Freq hz: " + ofToString(p_target*p_baseFreq), 10, 500);
    
    gui.draw();
}
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++) {
        float value = synth.tick();
        output[2*i] = value;
        output[2*i+1] = value;
    }
    
}
//--------------------------------------------------------------
void ofApp::adsrChanged(float &val){
    
    synth.setAttack(attack/1000.0);
    synth.setDecay(decay/1000.0);
    synth.setSustain(sustain);
    synth.setRelease(release/1000.0);
    synth.setGain(gain);
    synth.setAttackTarget(attackTarget);
    
    synth.setPitchAttack(p_attack/1000.0);
    synth.setPitchDecay(p_decay/1000.0);
    synth.setPitchRelease(p_release/1000.0);
    synth.setPitchTarget(p_target);
    synth.setPitchBaseFrequency(p_baseFreq);
    
    synth.setFilterCutoff(filterCutoff);
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        
        case ' ':
            synth.noteOn(440, gain);
            
        case '1':
            synth.setGeneratorType(SINE);
            break;
        case '2':
            synth.setGeneratorType(SQUARE);
            break;
        case '3':
            synth.setGeneratorType(SAW);
            break;
        case '4':
            synth.setGeneratorType(IMPULSE);
            break;
        case '5':
            synth.setGeneratorType(NOISE);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    synth.noteOff(.5);
    
}
//--------------------------------------------------------------
void ofApp::setupGui(){
    
    adsrParameters.setName("ADSR");
    adsrParameters.add(attack.set("attack(ms)",10, 1,2000));
    adsrParameters.add(decay.set("decay(ms)",200, 1,2000));
    adsrParameters.add(sustain.set("sustain",1, 0, 1));
    adsrParameters.add(release.set("release(ms)",500, 1,2000));
    adsrParameters.add(gain.set("gain",.5,0,1));
    adsrParameters.add(attackTarget.set("attack target", 1.0, 0.0, 1.0));
    
    
    pitchEnvParameters.setName("Pitch Env");
    pitchEnvParameters.add(p_attack.set("attack(ms)",10, 1,2000));
    pitchEnvParameters.add(p_decay.set("decay(ms)",200, 1,2000));
    pitchEnvParameters.add(p_release.set("release(ms)",500, 1,2000));
    pitchEnvParameters.add(p_target.set("target", 0.5, 0.0, 1.0));
    pitchEnvParameters.add(p_baseFreq.set("base Freq", 440, 50, 11000));
    
    
    gui.setup("Settings");
    
    gui.add(adsrParameters);
    gui.add(pitchEnvParameters);
    gui.add(filterCutoff.set("filterCutoff", 0.0, 0.0, 0.99));
    
    gui.setSize(600, 300);
    gui.setWidthElements(600);
    
    attack.addListener(this, &ofApp::adsrChanged);
    decay.addListener(this, &ofApp::adsrChanged);
    sustain.addListener(this, &ofApp::adsrChanged);
    release.addListener(this, &ofApp::adsrChanged);
    gain.addListener(this, &ofApp::adsrChanged);
    attackTarget.addListener(this, &ofApp::adsrChanged);
    
    p_attack.addListener(this, &ofApp::adsrChanged);
    p_decay.addListener(this, &ofApp::adsrChanged);
    p_release.addListener(this, &ofApp::adsrChanged);
    p_target.addListener(this, &ofApp::adsrChanged);
    p_baseFreq.addListener(this, &ofApp::adsrChanged);
    
    filterCutoff.addListener(this, &ofApp::adsrChanged);
    
    gui.loadFromFile("settings.xml");
    
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









