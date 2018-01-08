#pragma once
#include "ofMain.h"

class GameEvent : public ofEventArgs {
    
public:

    string   message,vidSrc;
	int id;
    
    GameEvent() {
		message = "";
		vidSrc = "";
		id = -1;
    }
    
    static ofEvent <GameEvent> events;
};

