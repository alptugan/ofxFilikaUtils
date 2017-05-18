//
//  ofxXmlParser.h
//  ofxFilikaUtils
//
//  Created by alp tugan on 11/04/16.
//
//

#ifndef __ofxXmlParser__
#define __ofxXmlParser__


#include "ofMain.h"
/*#if defined OF_TARGET_IPHONE
    #include "ofxiOS.h"
#endif*/

#include "ofxXmlSettings.h"

class ofxXmlParser  {
    
public:
    bool load(const string& xmlFile);
    vector<string> getTagList(string tagName, string _root = "root");
    vector<string> getAttrList(string tagName, string attrName,string _root = "root");
    string get(string tagName, string _root = "root");
    
    void unload();
    ofxXmlSettings file;
    bool isLoaded;
};

#endif /* defined(__ofxXmlParser__) */
