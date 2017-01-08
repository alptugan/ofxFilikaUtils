//
//  ofxInteractiveObject.h
//  GPSDataSimulation
//
//  Created by alp tugan on 31/12/16.
//
//

#ifndef ofxInteractiveObject_h
#define ofxInteractiveObject_h

#define		IDLE_COLOR		0xFFFFFF
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0xFF0000

#define CENTER 1
#define CORNER 0



#include "ofxMSAInteractiveObject.h"

class ofxInteractiveObject : public ofxMSAInteractiveObject{

public:
    

    int currentId;
    ofColor idleColor;
    ofColor overColor;
    ofColor downColor;
    
    bool isActive() {
        return _isSelected;
    };
    
    void setActive(bool _isSelected) {
        this->_isSelected = _isSelected;
    };
    
    
    void setColors(ofColor _idleColor = ofColor(255,204,0) ,
                   ofColor _overColor = ofColor(39,174,96),
                   ofColor _downColor = ofColor(231,76,60)) {
        
        idleColor = _idleColor;
        overColor = _overColor;
        downColor = _downColor;
        
        
    }

    void setPivotPoint(int pp = 0) {
        pivotPoint = pp;
        
        switch (pp) {
            case CORNER:
                pPt = ofPoint(0,0);
                break;
                
            case CENTER:
                pPt = ofPoint(width*0.5,height*0.5);
                break;
            default:
                break;
        }
    };
    
    
    
    void setup() {
        printf("MyTestObject::setup() - hello!\n");
        enableMouseEvents();
        enableKeyEvents();
    };
    
    
    void exit() {
        printf("MyTestObject::exit() - goodbye!\n");
    };
    
    
    void update() {
        //		x = ofGetWidth()/2 + cos(ofGetElapsedTimef() * 0.2) * ofGetWidth()/4;
        //		y = ofGetHeight()/2 + sin(ofGetElapsedTimef() * 0.2) * ofGetHeight()/4;
        
        if(isMousePressed(0)) {
            //setPosition(getMouseX() - ox, getMouseY() - oy);
            
        }else{
            xp = getPosition().x;
            yp = getPosition().y;
        }
    };
    
    
    void draw() {
        
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,50);
        ofDrawBitmapStringHighlight("x:" + ofToString(x) + " y:" + ofToString(y), x+5, y+15,
                                    ofColor(0,0,0,100));
        
        ofDrawBitmapStringHighlight("w:" + ofToString(this->width) + " h:" + ofToString(this->height), x+5, y+36,
                                    ofColor(0,0,0,100));
        
        if(onPressed) ofSetHexColor(DOWN_COLOR);
        else if(isMouseOver()) ofSetHexColor(OVER_COLOR);
        else ofSetHexColor(IDLE_COLOR);
        
        
        if(mode == "CORNER")
            ofDrawRectangle(x, y, width, height);
        
        else if(mode == "CENTER") {
            ofFill();
            ofPushMatrix();
            //ofTranslate();
            ofDrawEllipse(x,y,width,height);
            ofPopMatrix();
        }
        /*
        ofFill();
        ofRect(x-4,y-4, 9, 9);
        ofRect(x + width-5,y-4,9, 9);
        ofRect(x + width-5,y + height - 5,9, 9);
        ofRect(x-4,y + height - 5, 9, 9);
        ofNoFill();
        
        
        ofRect(x, y, width, height);
        
        
        // Pivot Point
        ofPushMatrix();
        ofTranslate(pPt.x,pPt.y);
        ofSetHexColor(0xff0000);
        ofLine(x-5,y,x+5,y);
        ofLine(x,y-5,x,y+5);
        
        ofPopMatrix();
        */
        
    };
    
    virtual void mousePressed(int x, int y, int button) {
        globalMouseButton = button;
    };
    
    virtual void mouseDragged(int x, int y, int button) {
        if(button == 0 && onPressed) {
            setPosition(x - ox, y - oy);
        }
    };
    
    virtual void onRollOver(int x, int y) {
        //printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
    }
    
    virtual void onRollOut() {
        //printf("MyTestObject::onRollOut()\n");
    }
    
    virtual void onMouseMove(int x, int y){
        //printf("MyTestObject::onMouseMove(x: %i, y: %i)\n", x, y);
        
        
    }
    
    virtual void onDragOver(int x, int y, int button) {
        //printf("MyTestObject::onDragOver(x: %i, y: %i, button: %i)\n", x, y, button);
        setPosition(x - ox, y - oy);
    }
    
    virtual void onDragOutside(int x, int y, int button) {
        //printf("MyTestObject::onDragOutside(x: %i, y: %i, button: %i)\n", x, y, button);
        if(isMousePressed(0)) {
            setPosition(getMouseX() - ox, getMouseY() - oy);
            
        }
    }
    
    virtual void onPress(int x, int y, int button) {
        //printf("MyTestObject::onPress(x: %i, y: %i, button: %i, ID: %i)\n", x, y, button, currentId);
        onPressed = true;
        
        ox = x - xp;
        oy = y - yp;
    }
    
    virtual void onRelease(int x, int y, int button) {
        //printf("MyTestObject::onRelease(x: %i, y: %i, button: %i)\n", x, y, button);
        onPressed = false;
        xp = x;
        yp = y;
    }
    
    virtual void onReleaseOutside(int x, int y, int button) {
        //printf("MyTestObject::onReleaseOutside(x: %i, y: %i, button: %i)\n", x, y, button);
    }
    
    virtual void keyPressed(int key) {
        //printf("MyTestObject::keyPressed(key: %i)\n", key);
    }
    
    virtual void keyReleased(int key) {
        //printf("MyTestObject::keyReleased(key: %i)\n", key);
    }
    
protected:
    bool _isSelected;
    bool onPressed = false;
    int xp;
    int yp;
    
    int ox;
    int oy;
    
    int globalMouseButton = -1;
    
    string pivotPoint;
    ofPoint pPt;
};

#endif /* ofxInteractiveObject_h */
