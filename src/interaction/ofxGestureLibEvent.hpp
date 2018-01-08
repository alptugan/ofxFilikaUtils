//
//  ofxGestureLibEvent.hpp
//  gestureRecognizer
//
//  Created by alp tugan on 02/06/17.
//
//

#ifndef ofxGestureLibEvent_hpp
#define ofxGestureLibEvent_hpp

#include "ofMain.h"

class ofxGestureLibEvent : public ofEventArgs {
    
public:
    
    string   message;
    int id;
    
    ofxGestureLibEvent() {
        message = "";
        id = -1;
    }
    
    static ofEvent <ofxGestureLibEvent> events;
};

#endif /* ofxGestureLibEvent_hpp */
