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
    
    instructions.loadFont("verdana.ttf", 20);
    
    gui.setup("Settings");
    gui.add(attack.setup("attack(ms)",10, 1,2000));
    gui.add(decay.setup("decay(ms)",200, 1,2000));
    gui.add(sustain.setup("sustain",1, 0, 1));
    gui.add(release.setup("release(ms)",500, 1,2000));
    gui.add(gain.setup("gain",.5,0,1));
    gui.add(attackTarget.setup("attack target", 1.0, 0.0, 1.0));
    gui.add(sustainLevel.setup("sustain level", 0.5, 0.0, 1.0));
    gui.add(octave.setup("octave", 3, 1, 6));
    
    
    synth.setAttack(attack/1000.0);
    synth.setDecay(decay/1000.0);
    synth.setSustain(sustain);
    synth.setRelease(release/1000.0);
    synth.setGain(gain);
    
    attack.addListener(this, &ofApp::adsrChanged);
    decay.addListener(this, &ofApp::adsrChanged);
    sustain.addListener(this, &ofApp::adsrChanged);
    release.addListener(this, &ofApp::adsrChanged);
    gain.addListener(this, &ofApp::adsrChanged);
    attackTarget.addListener(this, &ofApp::adsrChanged);
    sustainLevel.addListener(this, &ofApp::adsrChanged);
    
    ofSoundStreamSetup(2, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    instructions.drawString("Press a,s,d,f,g,h,j,k,l to play your wave\n1:SINE - 2: SQUARE - 3:SAW - 4:IMPULSE - 5:NOISE ", 250, 100);
    
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
    synth.setSustainLevel(sustainLevel);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // openframeworks calls keyPressed() even when key is heldDown
    // so we have check if key is already held down before calling noteOn
    
    int oct = octave;
    
    if (key == 'a') {
        if (!aDown) {
            synth.noteOn(NoteC * oct, gain);
            aDown = true;
        }
    }else if (key == 's'){
        if (!sDown) {
            synth.noteOn(NoteD * oct, gain);
            sDown = true;
        }
    }else if (key == 'd'){
        if (!dDown) {
            synth.noteOn(NoteE * oct, gain);
            dDown = true;
        }
    }else if (key == 'f'){
        if (!fDown) {
            synth.noteOn(NoteF * oct, gain);
            fDown = true;
        }
    }else if (key == 'g'){
        if (!gDown) {
            synth.noteOn(NoteG * oct, gain);
            gDown = true;
        }
    }else if(key == 'h'){
        if (!hDown) {
            synth.noteOn(NoteA * oct, gain);
            hDown = true;
        }
    }else if (key == 'j'){
        if (!jDown) {
            synth.noteOn(NoteB * oct, gain);
            jDown = true;
        }
        
    }else if (key =='k'){
        if (!kDown) {
            synth.noteOn(NoteC2 * oct, gain);
            kDown = true;
        }
    }else if (key == 'l'){
        if (!lDown) {
            synth.noteOn(NoteD2 * oct, gain);
            lDown = true;
        }
    }
    
    switch (key) {
            
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
    switch (key) {
        case 'a':
            aDown = false;
            break;
        case 's':
            sDown = false;
            break;
        case 'd':
            dDown = false;
            break;
        case 'f':
            fDown = false;
            break;
        case 'g':
            gDown = false;
            break;
        case 'h':
            hDown = false;
            break;
        case 'j':
            jDown = false;
            break;
        case 'k':
            kDown = false;
            break;
        case 'l':
            lDown = false;
        default:
            break;
    }
    
    // have to do this check to allow legato style playing
    if (noNotesDown()) {
        synth.noteOff(.5);
    }
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

bool ofApp::noNotesDown() const{
    if (!(aDown || sDown || dDown || fDown || gDown || hDown || jDown || kDown || lDown)) {
        return true;
    }else{
        return false;
    }
}







