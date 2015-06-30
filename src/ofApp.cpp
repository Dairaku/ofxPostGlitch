#include "ofApp.h"
#define SCSHOTS_PER_SEC 10 //SCSHOTS_PER_SECは一秒間あたりの表示画像数。
#define NUM_IMG 10//NUM_IMGは 画像の枚数である。


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(60);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    myFbo.allocate(ofGetWidth(), ofGetHeight());
    myGlitch.setup(&myFbo);
    myFbo1.allocate(ofGetWidth(),ofGetHeight());
    
    int i = 1;
    string fileName = "0001.jpeg";
    while (ofFile::doesFileExist(fileName)){
        ofImage aImage;
        aImage.loadImage(fileName);
        image.push_back(aImage);
        i++;
        char char1[32];
        sprintf(char1, "%04d.jpeg", i);
        fileName = ofToString(char1);
    }
    currentFrame =0;//高速でイメージを描写
    
    ttf.loadFont(OF_TTF_SANS, 100);//ofTrueTypeFontのインスタンス.loadFont(文字の種類,文字の高さ)
    s = "Schoenberg";
    
    bdrawimage =false;
    bdrawtitle = false;
    
    mySound.loadSound("sample1.mp3"); //サウンドファイルの読込み
    mySound.setLoop(true); //ループ再生をONに
    mySound.play(); //サウンド再生開始
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bdrawtitle){
        myFbo.begin();
        ofBackground(0);
        ofRectangle r = ttf.getStringBoundingBox(s, 0, 0);////フォントを取り囲む長方形を計算
        ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f));
        ofSetColor(255);
        ttf.drawString(s, ofGetWidth()/2 + offset.x, ofGetHeight()/2+ offset.y);//インスタンス(文字列、場所)
        myFbo.end();
    }
    if(bdrawimage){
        myFbo1.begin();
        ofClear(0, 0, 0, 255);
        if (ofGetFrameNum()%(60/SCSHOTS_PER_SEC)==0)currentFrame++;
        if (currentFrame >= NUM_IMG) currentFrame = 0;
        image[currentFrame].draw(0,0,ofGetWidth(),ofGetHeight());
        myFbo1.end();
    }
    
    if(shaderSwitch&&bdrawtitle){
        shaderIndex=ofRandom(1,17);
        if(ofGetElapsedTimeMillis()%1000<300){
            if (shaderIndex == 1) myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
            if (shaderIndex == 2) myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
            if (shaderIndex == 3) myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
            if (shaderIndex == 4) myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
            if (shaderIndex == 5) myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
            if (shaderIndex == 6) myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
            if (shaderIndex == 7) myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
            if (shaderIndex == 8) myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
            if (shaderIndex == 9) myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
            if (shaderIndex == 10) myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
            
            if (shaderIndex == 11) myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
            if (shaderIndex == 12) myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
            if (shaderIndex == 13) myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
            if (shaderIndex == 14) myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
            if (shaderIndex == 15) myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
            if (shaderIndex == 16) myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
            if (shaderIndex == 17) myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
        }else{
            if (shaderIndex == 1) myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
            if (shaderIndex == 2) myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
            if (shaderIndex == 3) myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
            if (shaderIndex == 4) myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
            if (shaderIndex == 5) myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
            if (shaderIndex == 6) myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
            if (shaderIndex == 7) myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
            if (shaderIndex == 8) myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
            if (shaderIndex == 9) myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
            if (shaderIndex == 10) myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
            
            if (shaderIndex == 11) myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
            if (shaderIndex == 12) myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
            if (shaderIndex == 13) myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
            if (shaderIndex == 14) myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
            if (shaderIndex == 15) myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
            if (shaderIndex == 16) myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
            if (shaderIndex == 17) myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
            
        }
    }
    else{
        myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
        myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
        myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
        myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
        myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
        myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
        myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
        myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
        myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
        
        myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
        myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch(int(ofGetElapsedTimef())%4){
        case 0:case 1:{
            bdrawimage = true;
            bdrawtitle = false;
            break;
        }
        case 2:case 3:{
            bdrawimage = false;
            bdrawtitle = true;
            break;
        }
    }//switch文終わり
    if(bdrawtitle){
        myGlitch.generateFx();
        myFbo.draw(0,0);
    }
    if(bdrawimage){
        myFbo1.draw(0,0);
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        shaderSwitch=!shaderSwitch;
    }
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

