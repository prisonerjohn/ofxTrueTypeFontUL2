//
//  ofxFTGLFontUL2.cpp
//  emptyExample
//
//  Created by Elias Zananiri on 1/22/15.
//
//

#include "ofxFTGLFontUL2.h"

//--------------------------------------------------
ofRectangle ofxFTGLFontUL2::getStringBoundingBox(wstring s, float x, float y, float width, float height, int textAlign)
{
    if (loaded && width > 0) {
        setLineLength(width);
    }
    return ofxFTGLSimpleLayout::getStringBoundingBox(s, x, y);
}

//--------------------------------------------------
ofRectangle ofxFTGLFontUL2::getStringBoundingBox(string s, float x, float y, float width, float height, int textAlign)
{
    if (loaded && width > 0) {
        setLineLength(width);
    }
    return ofxFTGLSimpleLayout::getStringBoundingBox(s, x, y);
}

//--------------------------------------------------
void ofxFTGLFontUL2::drawString(wstring s, float x, float y, float width, float height, int textAlign)
{
    if (loaded) {
        if (width > 0) {
            setLineLength(width);
        }
        setAlignment((ofxFTGLTextAlignment)textAlign);
        
        ofxFTGLSimpleLayout::drawString(s, x, y + getAscender());
    }
}

//--------------------------------------------------
void ofxFTGLFontUL2::drawString(string s, float x, float y, float width, float height, int textAlign)
{
    if (loaded) {
        if (width > 0) {
            setLineLength(width);
        }
        setAlignment((ofxFTGLTextAlignment)textAlign);

        ofxFTGLSimpleLayout::drawString(s, x, y + getAscender());
    }
}

//--------------------------------------------------
void ofxFTGLFontUL2::drawStringAsShapes(wstring s, float x, float y, float width, float height, int textAlign)
{
    drawString(s, x, y, width, height, textAlign);
}

//--------------------------------------------------
void ofxFTGLFontUL2::drawStringAsShapes(string s, float x, float y, float width, float height, int textAlign)
{
    drawString(s, x, y, width, height, textAlign);
}

//--------------------------------------------------
void ofxFTGLFontUL2::setLineHeight(float height)
{
    setLineSpacing(height / getSize());
}

//--------------------------------------------------
float ofxFTGLFontUL2::getLineHeight()
{
    return getLineSpacing() * getSize();
}
