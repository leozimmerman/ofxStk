#include "ofApp.h"

using namespace stk;

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
    
    synth.setPitchAttack(p_attack/1000.0);
    synth.setPitchDecay(p_decay/1000.0);
    synth.setPitchRelease(p_release/1000.0);
    synth.setPitchTarget(p_target);
    synth.setPitchBaseFrequency(p_baseFreq);
    
    synth.setNoiseAttack(n_attack/1000.0);
    synth.setNoiseDecay(n_decay/1000.0);
    synth.setNoiseSustain(n_sustain);
    synth.setNoiseRelease(n_release/1000.0);
    
    
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
    font.drawString("Press spacebar to play sound", 10, 450);
    
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
    
    synth.setPitchAttack(p_attack/1000.0);
    synth.setPitchDecay(p_decay/1000.0);
    synth.setPitchRelease(p_release/1000.0);
    synth.setPitchTarget(p_target);
    synth.setPitchBaseFrequency(p_baseFreq);
    
    synth.setNoiseAttack(n_attack/1000.0);
    synth.setNoiseDecay(n_decay/1000.0);
    synth.setNoiseSustain(n_sustain);
    synth.setNoiseRelease(n_release/1000.0);
    
    synth.setLowPassCutoff(lowPassCutoff);
    synth.setHighPassCutoff(highPassPassCutoff);

    synth.setGain(gain);
    
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
    
    sineAdsrParameters.setName("Sine ADSR");
    sineAdsrParameters.add(attack.set("attack(ms)",10, 1,2000));
    sineAdsrParameters.add(decay.set("decay(ms)",200, 1,2000));
    sineAdsrParameters.add(sustain.set("sustain level", 0.5, 0, 1));
    sineAdsrParameters.add(release.set("release(ms)",500, 1,2000));
    
    pitchAdsrParameters.setName("Pitch ADSR");
    pitchAdsrParameters.add(p_attack.set("attack(ms)",10, 1,2000));
    pitchAdsrParameters.add(p_decay.set("decay(ms)",200, 1,2000));
    pitchAdsrParameters.add(p_release.set("release(ms)",500, 1,2000));
    pitchAdsrParameters.add(p_target.set("target", 0.5, 0.0, 1.0));
    pitchAdsrParameters.add(p_baseFreq.set("base Freq", 440, 50, 11000));
    
    noiseAdsrParameters.setName("Noise ADSR");
    noiseAdsrParameters.add(n_attack.set("attack(ms)",10, 1,2000));
    noiseAdsrParameters.add(n_decay.set("decay(ms)",200, 1,2000));
    noiseAdsrParameters.add(n_sustain.set("sustain level", 0.5, 0, 1));
    noiseAdsrParameters.add(n_release.set("release(ms)",500, 1,2000));
    
    gui.setup("Settings");
    
    gui.add(sineAdsrParameters);
    gui.add(pitchAdsrParameters);
    gui.add(noiseAdsrParameters);
    gui.add(lowPassCutoff.set("LowPass Cutoff", 0.0, 0.0, 0.99));
    gui.add(highPassPassCutoff.set("HighPass Cutoff", 0.0, 0.0, 0.99));
    gui.add(gain.set("gain",.5,0,1));
    
    gui.setSize(600, 300);
    gui.setWidthElements(600);
    
    attack.addListener(this, &ofApp::adsrChanged);
    decay.addListener(this, &ofApp::adsrChanged);
    sustain.addListener(this, &ofApp::adsrChanged);
    release.addListener(this, &ofApp::adsrChanged);
    
    
    p_attack.addListener(this, &ofApp::adsrChanged);
    p_decay.addListener(this, &ofApp::adsrChanged);
    p_release.addListener(this, &ofApp::adsrChanged);
    p_target.addListener(this, &ofApp::adsrChanged);
    p_baseFreq.addListener(this, &ofApp::adsrChanged);
    
    n_attack.addListener(this, &ofApp::adsrChanged);
    n_decay.addListener(this, &ofApp::adsrChanged);
    n_sustain.addListener(this, &ofApp::adsrChanged);
    n_release.addListener(this, &ofApp::adsrChanged);
    
    gain.addListener(this, &ofApp::adsrChanged);
    lowPassCutoff.addListener(this, &ofApp::adsrChanged);
    highPassPassCutoff.addListener(this, &ofApp::adsrChanged);
    
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









