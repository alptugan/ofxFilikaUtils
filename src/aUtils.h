//
//  aUtils.h
//  big_n_bold_shakeshake_v2
//
//  Created by alp tugan on 19/02/15.
//
//

#ifndef big_n_bold_shakeshake_v2_aUtils_h
#define big_n_bold_shakeshake_v2_aUtils_h

#include "ofMain.h"


//#include "ofxThreadedTimer.h"


//#include "ofxFontStash.h"
#include "ofxHotKeys.h"

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600

template <typename T>
string NumberToString(T pNumber)
{
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}

static ofXml XML;
static int num;
static string node;
static bool isAppModeEnabled;

static bool timeSet;
static float timeBegan;
//--------------------------------------------------------------
// READ XML
static void readXML(string path,string nodeName) {
    
    XML.reset();
    
    XML.load(path);
    
    // Move to root same as XML.setTo(rootNode);
    XML.setToSibling();
    
    
    //
    
    num = XML.getNumChildren(nodeName);
 
    //cout << "xml : " << num << endl;
    node = nodeName;
    //tweets.resize(num);
   /*
    for (int i = 0; i < num; i++) {
        
        string n = NumberToString(i);
        string s;
        int v;
        
        s = XML.getValue("image["+n+"]/imageSrc");
        //v = ofToInt(XML.getValue("image["+n+"]/skorVal"));
        //XML.setToParent();
        
        //skores.push_back(v);
        //fileNames.push_back(s);
        cout << "Image list : " << s << endl;
    }*/
}

static vector <string> getStringNodeList(string nodeName) {
    
    vector <string> fileNames;
    
    for (int i = 0; i < num; i++) {
        
        string n = NumberToString(i);
        string s;
        int v;
        
        s = XML.getValue(node +"["+n+"]/" + nodeName);
        //v = ofToInt(XML.getValue("image["+n+"]/skorVal"));
        //XML.setToParent();
        
        //skores.push_back(v);
        fileNames.push_back(s);
        //cout << "Image list : " << s << endl;
    }
    

    return fileNames;
}

static vector <int> getIntNodeList(string nodeName) {
    
    vector <int> fileNames;
    
    for (int i = 0; i < num; i++) {
        
        string n = NumberToString(i);
        int s;
        int v;
        
        s = XML.getIntValue(node +"["+n+"]/" + nodeName);
        //v = ofToInt(XML.getValue("image["+n+"]/skorVal"));
        //XML.setToParent();
        
        //skores.push_back(v);
        fileNames.push_back(s);
        cout << "Image list : " << s << endl;
    }
    
    
    return fileNames;
}

/*
ofxThreadedTimer &createTimer(int gameTime) {
    // Remaining Time
    ofxThreadedTimer * timer;
    timer->setup(gameTime*1000, false);
    timer->startTimer();
    
    //ofAddListener(timer.TIMER_REACHED,this,&newResponse);
    
    return *timer;
}
*/

//-----------------------------------------
// Game Time
static string calculateTime(int gameTime, float currentTime) {
    
    int seconds;
    int minutes;
    int mins_left;
    int secs_left;
    
    seconds = (gameTime - int(currentTime/1000));
    minutes = (gameTime - int(currentTime/1000)) / SECS_PER_MIN;
    mins_left = minutes % SECS_PER_MIN;
    secs_left = seconds % SECS_PER_MIN;
    
    string mins;
    string secs;
    
    if(mins_left < 10) {
        mins = "0"+ofToString(mins_left);
    }else {
        mins = ofToString(mins_left);
    }
    
    if(secs_left < 10) {
        secs = "0"+ofToString(secs_left);
    }else {
        secs = ofToString(secs_left);
    }
    
    
    //cout << ofGetElapsedTimeMillis() / 1000 << endl;
    //cout << "remaining time : " << mins_left << " : " <<  secs_left << endl;
    //cout << "remaining time : " << mins << " : " <<  secs << endl;
    
    if(mins_left < 0 || secs_left < 0)
        return "00:00";
    else
        return (mins + ":" + secs);
    //return ofToString(seconds);
}

// Animation loop based on time and framerate on vertical axis
static float sinWaveAnimation(float _moveAmount = 5, float _freq = 0.1, int _per_second = 0) {
    
    return (_per_second > 0) ? (ofGetSeconds() % _per_second == 0 ? _moveAmount * sin(ofGetFrameNum()*_freq) * (30.0 / ofGetFrameRate()) : 0) : _moveAmount * sin(ofGetFrameNum()*_freq) * (30.0 / ofGetFrameRate());
}

// Animation loop based on time and framerate on horizontal axis
static float cosWaveAnimation(float _moveAmount = 5, float _freq = 1, int _per_second = 0) {
    
    if(_per_second > 0) {
        if(ofGetSeconds() % _per_second == 0 ) {
            return _moveAmount * cos(ofGetFrameNum()*_freq) * (30.0 / ofGetFrameRate());
        }
    }else{
        return _moveAmount * cos(ofGetFrameNum()*_freq) * (30.0 / ofGetFrameRate());
    }
    
}
/*
static int yoyoMovement(int step, int from,int to) {
    
    if(isYoyoSwitched) {
        newVal = newVal - step;
        
        if(newVal <= from) {
            isYoyoSwitched = !isYoyoSwitched;
            
        }
    }else{
        newVal = newVal + step;
        
        if(newVal >= to)
            isYoyoSwitched = !isYoyoSwitched;
    }
    
    
        
    
    return newVal;
}

*/
// Ticking boolean to notify user per interval
static bool notifyPerSeconds(int _per_second) {
    
    return (ofGetSeconds() % _per_second == 0) ?  true : false;
}


static bool notifyPerSecondf(float stageCylceTime) {
    if(!timeSet) {
        timeBegan = ofGetElapsedTimef();
        timeSet = true;
    }
    
    if( ofGetElapsedTimef() > timeBegan + stageCylceTime) {
        timeSet  = false;
        return true;
    }else{
        return false;
    }
    
    
    
}

/*
static int getStrWidth(ofxFontStash *f,string str, int _size) {
    
    return f->getBBox(str, _size, 0, 0).getWidth();
    
    delete f;
}
*/

// Game Mode On/Off
static void setAppMode(bool _c) {
    isAppModeEnabled = _c;
    if(_c) {
        ofHideCursor();
    }else{
        ofShowCursor();
    }
    
    ofSetFullscreen(_c);
}

static bool getAppMode() {
    return isAppModeEnabled;
}

// distance 3D
static float ofxDistance3D(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

// Color
static ofColor ofxGetPixelColor(ofBaseHasPixels &img, int x, int y, int w, int h, int bpp=3) {
    ofColor c;
    int i = y*w*bpp + x*bpp;
    c.r = img.getPixels()[i+0];
    c.g = img.getPixels()[i+1];
    c.b = img.getPixels()[i+2];
    if (bpp==4) c.a = img.getPixels()[i+3];
    return c;
}

static ofColor ofxGetPixelColor(int x, int y) {
    ofImage img;
    img.grabScreen(x,y,1,1);
    return ofxGetPixelColor(img,0,0,1,1);
}

static void ofxSetColor(int hexColor, int a) { //alpha between 0..255
    int r = (hexColor >> 16) & 0xff;
    int g = (hexColor >> 8) & 0xff;
    int b = (hexColor >> 0) & 0xff;
    ofSetColor(r,g,b,a);
}

static void ofxSetColorHSB(float h, float s, float b, float a) {
    if (b==0) return ofSetColor(0,0,0,a); //black
    if (s==0) return ofSetColor(b,b,b,a); //gray
    
    h *= 6.0 / 255.0;
    s *= 1.0 / 255.0;
    
    float x = b * (1-s);
    float y = b * (1-s*(h-int(h)));
    float z = b * (1-s*(1-(h-int(h))));
    
    switch (int(h)) {
        case 0: return ofSetColor(b,z,x,a); //red
        case 1: return ofSetColor(y,b,x,a); //green
        case 2: return ofSetColor(x,b,z,a);
        case 3: return ofSetColor(x,y,b,a); //blue
        case 4: return ofSetColor(z,x,b,a);
        case 5: return ofSetColor(b,x,y,a); //back to red
    }
}

static bool ofxColorMatch(ofColor a, ofColor b, int tolerance) {
    return ofxDistance3D(a.r,a.g,a.b,b.r,b.g,b.b)<=tolerance;
}


// String
bool hasEnding(std::string const &fullString, std::string const &ending){
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}



// String
static string ofxTrimStringRight(string str) {
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

static string ofxFormatString(string format, int number) {
    char buffer[100];
    sprintf(buffer, format.c_str(), number);
    return (string)buffer;
}

static bool ofxStringStartsWith(string &str, string &key) {
    return str.find(key) == 0;
}

static bool ofxStringEndsWith(string &str, string& key) {
    //http://www.codeproject.com/KB/stl/STL_string_util.aspx?display=Print
    size_t i = str.rfind(key);
    return (i != string::npos) && (i == (str.length() - key.length()));
}

// File IO
static string ofxGetFileExtension(string filename) {
    int pos = filename.rfind('.');
    if (pos==string::npos) return "";
    return filename.substr(pos);
}

static bool ofxFileExists(string filename) {
    ifstream inp;
    inp.open(ofToDataPath(filename).c_str(), ifstream::in);
    inp.close();
    return !inp.fail();
}

static vector<string> ofxReadLines(string filename) {
    vector<string> lines;
    filename = ofToDataPath(filename);
    if (!ofxFileExists(filename)) cout << ("File not found: " + filename) << endl;
    ifstream f(filename.c_str(),ios::in);
    string line;
    while (getline(f,line)) lines.push_back(ofxTrimStringRight(line));
    f.close();
    return lines;
}

static void drawFrameRate() {
    ofDrawBitmapStringHighlight("FPS : " + ofToString(floor(ofGetFrameRate())), ofGetWidth() - 80, ofGetHeight() - 20);
}

#endif
