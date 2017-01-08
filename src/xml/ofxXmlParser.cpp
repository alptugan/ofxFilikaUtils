//
//  ofxXmlParser.cpp
//  aksoyClients_ipad
//
//  Created by alp tugan on 11/04/16.
//
//

#include "ofxXmlParser.h"

bool ofxXmlParser::load(const string& xmlFile) {
    
/*#if defined OF_TARGET_IPHONE
    if( file.loadFile(ofxiOSGetDocumentsDirectory() + xmlFile) ){
        isLoaded = true;
    }else
#endif*/
        if( file.loadFile(xmlFile) ){
        isLoaded = true;
            ofLogNotice() << xmlFile << " load success";
    }else{
        isLoaded = false;
        ofLogError() << xmlFile << " load fail";
    }
    
    return isLoaded;
}

vector<string> ofxXmlParser::getTagList(string tagName, string _root) {
    vector<string> list;
    
    if(isLoaded) {
        
        
        // Move into root tag to acces items
        file.pushTag(_root);
        
        int menuItemNum = file.getNumTags(tagName);
        
        //cout << "num : " << menuItemNum << endl;
        
        list.clear();
        
        for (int i=0; i< menuItemNum; i++) {
            //cout << "content is . :::" << file.getAttribute("items:title", "content", "default",i) << endl;
            list.resize(i+1);
            list[i] = file.getValue(tagName, "noValueProvided",i);
        }
        
        file.popTag();
    }
    
    
    return list;
}

vector<string> ofxXmlParser::getAttrList(string tagName, string attrName, string _root) {
    vector<string> list;
    
    if(isLoaded) {
        
        // Move into root tag to acces items
        file.pushTag(_root);
        
        int menuItemNum = file.getNumTags(tagName);
        
        //cout << "num : " << menuItemNum << endl;
        
        list.clear();
        
        for (int i=0; i< menuItemNum; i++) {
            
            list.resize(i+1);
            list[i] = file.getAttribute(tagName,attrName, "noValueProvided",i);
            
            //cout << "content is . :::" << list[i] << endl;
        }
    }
    
    file.popTag();
    return list;
}