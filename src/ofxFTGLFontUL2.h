//
//  ofxFTGLFontUL2.h
//  emptyExample
//
//  Created by Elias Zananiri on 1/22/15.
//
//

#pragma once

#include "ofxFTGL.h"

class ofxFTGLFontUL2
: public ofxFTGLSimpleLayout
{
public:
    ofRectangle getStringBoundingBox(wstring s, float x, float y, float width);
    ofRectangle getStringBoundingBox(string s, float x, float y, float width);
    
    void drawString(wstring s, float x, float y, float width=0, float height=0, int textAlign=FTGL_ALIGN_LEFT);
	void drawString(string s, float x, float y, float width=0, float height=0, int textAlign=FTGL_ALIGN_LEFT);
    
    void drawStringAsShapes(wstring s, float x, float y, float width=0, float height=0, int textAlign=FTGL_ALIGN_LEFT);
	void drawStringAsShapes(string s, float x, float y, float width=0, float height=0, int textAlign=FTGL_ALIGN_LEFT);    
};
