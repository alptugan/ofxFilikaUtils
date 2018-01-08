//
//  backButton.h
//  aksoyClientIPadv2
//
//  Created by alp tugan on 18/02/16.
//
//

#ifndef aksoyClientIPadv2_backButton_h
#define aksoyClientIPadv2_backButton_h

//#include "ofxTrueTypeFontUC.h"
#include "ofMain.h"
#include "GameEvent.h"

class backButton {
    
public:
    //ofxTrueTypeFontUC * font;
	ofImage img;
	ofImage sticker;
	ofImage activePic;
	backButton(string src = "", string sub = "", int _id = 0, string _vid = "") {
		img.loadImage(src);
		fadeInCounter = 0;
		vid = _vid;
		if (sub != "") {
			sticker.loadImage(sub);
			h = img.getHeight() + sticker.getHeight();
			_sub = true;
		}
		else {
			_sub = false;
			h = img.getHeight();
		}
			
		id = _id;
		w = img.getWidth();
		
        result = false;
		ofRegisterMouseEvents(this);
		ofRegisterTouchEvents(this);

		isAnimatable = false;
		// must call this before adding any tweens //
		Tweenzor::init();
		scaleFactor = 265;
		x1 = 0;
		x2 = 360;
		delay = 0.0;
    }
    
    ~backButton() {
    }
    
    
    int getRad() {
        return w;
    }
    
	ofVec2f getPosition() {
		return ofVec2f(xpos-img.getWidth()*0.5, ypos-img.getHeight()*0.5);
	}

    bool hit(int x,int y) {

        hitx = x + img.getWidth()*0.5;
        hity = y + img.getHeight()*0.5;
        
        //result =  (x < xpos + w * 0.5 && x > xpos - w * 0.5 && y > ypos - w * 0.5 && y < ypos + w * 0.5) ? true : false;
        

		result =  (hitx < xpos + w && hitx > xpos && hity > ypos && hity < ypos + h) ? true : false;
        return result;
            
    }
    
	void setFadeSpeed(float _fadeSpeed) {
		fadeSpeed = _fadeSpeed;
	}

	void setFadeAnim(bool val) {
		fadeVideo = val;
	}

	void setIdleOsc(ofxOscSender & _sender, string _msg,int arg=1) {
		ofxOscMessage m;
		m.setAddress(_msg);
		m.addIntArg(arg);
		_sender.sendMessage(m, false);
		//fadeInCounter = 0.0;
		//fadeDir = 1;
		//fadeVideo = true; 

	}

	void setPowerOsc(ofxOscSender & _sender, string _msg) {
		ofxOscMessage m;
		m.setAddress(_msg);
		m.addIntArg(1);
		_sender.sendMessage(m, false);
		//fadeInCounter = 0.0;
		//fadeDir = 1;
		//fadeVideo = true; 
		
	}

	void fadeInVideo(ofxOscSender & _sender,string _msg) {
		if (fadeVideo) {


			fadeInCounter += fadeSpeed*fadeDir;

			if (fadeInCounter > 1.0 || fadeInCounter < 0.0) {
				fadeVideo = false;
				if (fadeInCounter > 1.0f) fadeInCounter = 1.0f;
				if (fadeInCounter < 0.0f) fadeInCounter = 0.0f;
			}

			cout << "buton class : " << fadeInCounter << endl;
	
			ofxOscMessage m;
			m.setAddress(_msg);
			m.addFloatArg(fadeInCounter);
			_sender.sendMessage(m, false);
			if(fadeInCounter < 1.0 && fadeInCounter > 0.0) {
				
			}
		}


	}

	
    //--------------------------------------------------------------
    void touchDown(ofTouchEventArgs & touch){
        hit(touch.x,touch.y);
    }
    
    //--------------------------------------------------------------
    void touchMoved(ofTouchEventArgs & touch){
        hit(touch.x,touch.y);
    }
    
    //--------------------------------------------------------------
    void touchUp(ofTouchEventArgs & touch){
        hit(touch.x,touch.y);
		if (result) {
			GameEvent e;
			e.message = "hit";
			e.vidSrc = vid;
			e.id = id;
			ofNotifyEvent(GameEvent::events, e);
		}
		result = false;
    }
    
    //--------------------------------------------------------------
    void touchDoubleTap(ofTouchEventArgs & touch){
    }
    
    //--------------------------------------------------------------
    void touchCancelled(ofTouchEventArgs & touch){
    }


	//--------------------------------------------------------------
	void mouseScrolled(ofMouseEventArgs & args) {

	}

	//--------------------------------------------------------------
	void mouseEntered(ofMouseEventArgs & args) {

	}

	//--------------------------------------------------------------
	void mouseExited(ofMouseEventArgs & args) {

	}
	//--------------------------------------------------------------
	void mouseMoved(ofMouseEventArgs & args) {

	}

	//--------------------------------------------------------------
	void mouseDragged(ofMouseEventArgs & args) {

	}

	//--------------------------------------------------------------
	void mousePressed(ofMouseEventArgs & args) {
		hit(args.x, args.y);
	}

	//--------------------------------------------------------------
	void mouseReleased(ofMouseEventArgs & args) {
		//hit(args.x, args.y);
		

		if(result) {
		GameEvent e;
		e.message = "hit";
		e.vidSrc = vid;
		e.id = id;
		ofNotifyEvent(GameEvent::events, e);
		}
		result = false;
	}

	void disableInteraction() {
		ofUnregisterMouseEvents(this);
		ofUnregisterTouchEvents(this);
	}

	void enableInteraction() {
		ofRegisterMouseEvents(this);
		ofRegisterTouchEvents(this);
	}

	void setAnimatable(bool _isAnimatable,float _del) {

		isAnimatable = _isAnimatable;
		delay = _del;

		if(isAnimatable) {
			params2.setup(&x1, x1, x2, _del, 0.5f, EASE_OUT_SINE);
			Tweenzor::add(params2);

			Tweenzor::addCompleteListener(Tweenzor::getTween(params2.property), this, &backButton::onComplete);

			
		}

	}

    
	void draw(int x, int y) {
		Tweenzor::update(ofGetElapsedTimeMillis());

		xpos = x + img.getWidth()*0.5;
		ypos = y + img.getHeight()*0.5;



		ofPushMatrix();
		ofTranslate(xpos, ypos);
		//ofScale(scaleFactor,scaleFactor);


		if (isAnimatable)
			ofRotateY(x1);

		ofTranslate(-img.getWidth()*0.5, -img.getHeight()*0.5);
		if (!result) {
			img.draw(0, 0);
			//ofNoFill();
			
			//ofDrawRectangle(0, 0, img.getWidth(), img.getHeight());
		}
		else {
			sticker.draw(0, 0);
		//activePic.draw(0, 0);
		}
		/*if(_sub)
			sticker.draw(0,0);*/

		ofPopMatrix();
    }

	//void onUpdate(float args);
	void onComplete(float* arg) {

		
		if (arg == &x1) {
			
			Tweenzor::removeCompleteListener(&x1);

			if(x1 > 10) {
				x2 = 0;
				params2.setup(&x1, x1, x2, 2.f + delay, 0.5f, EASE_OUT_SINE);
				Tweenzor::add(params2);
			}

			if (x1 < 10) {
				x2 = 360;
				params2.setup(&x1, x1, x2, 2.f + delay, 0.5f, EASE_OUT_SINE);
				Tweenzor::add(params2);
			}

			Tweenzor::addCompleteListener(Tweenzor::getTween(params2.property), this, &backButton::onComplete);
		}

	}
	string vid;
	bool result;
	float scaleFactor;
	float fadeInCounter, fadeSpeed;
	float fadeDir;
	bool fadeVideo;
private:
    int xpos, ypos, w, hitx, hity,id,h ;
	bool _sub;
    
	bool isAnimatable,delay;
	

	// Tween Lib
	float x1, x2;
	
	TweenParams params2;
};
#endif
