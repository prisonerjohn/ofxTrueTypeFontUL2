//
//  ofxTextLabelUL2.cpp
//  emptyExample
//
//  Created by Elias Zananiri on 2015-01-05.
//
//

#include "ofxTextLabelUL2.h"
#include "ofxTextUtilsUL2.h"

//--------------------------------------------------
ofxTextLabelUL2::ofxTextLabelUL2()
: _text(L"")
, _drawBounds(0, 0, 0, 0)
, _bDrawShapes(false)
, _align(UL2_TEXT_ALIGN_INVALID)
, _bNeedsRebuild(false)
, _bValidTotalBounds(false)
, _bValidGlyphBounds(false)
{
    
}

//--------------------------------------------------
ofxTextLabelUL2::~ofxTextLabelUL2()
{

}

//--------------------------------------------------
void ofxTextLabelUL2::rebuild()
{
    // Reallocate the FBO if necessary.
    float totalWidth = _drawBounds.x * 2 + _drawBounds.width;
    float totalHeight = _drawBounds.x * 2 + _drawBounds.width;
    // EZ: We could test that the dims are greater or equal instead if this turns out to be slow.
    if (_fbo.getWidth() != totalWidth || _fbo.getHeight() != totalHeight) {
        _fboSettings.width = totalWidth;
        _fboSettings.height = totalHeight;
		_fboSettings.internalformat = GL_RGBA;
        _fbo.allocate(_fboSettings);
    }
    
    _fbo.begin();
    {
        ofClear(clearColor.r,clearColor.g,clearColor.b,0);
        
        ofPushStyle();
        
        ofSetColor(255);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
        if (_bDrawShapes) {
            font.drawStringAsShapes(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        }
        else {
            font.drawString(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        }
		ofDisableAlphaBlending();
        ofPopStyle();
    }
    _fbo.end();
    
    _bValidTotalBounds = false;
    _bValidGlyphBounds = false;
    _bNeedsRebuild = false;
}

//--------------------------------------------------
bool ofxTextLabelUL2::update()
{
    if (_bNeedsRebuild && font.isLoaded()) {
        rebuild();
        return true;
    }
    return false;
}

//--------------------------------------------------
void ofxTextLabelUL2::draw(float x, float y) const
{
    _fbo.draw(x, y);
}

//--------------------------------------------------
void ofxTextLabelUL2::draw(float x, float y, float w, float h) const
{
    _fbo.draw(x, y, w, h);
}

void ofxTextLabelUL2::setText(const string& text)
{
    setText(ofStringUTF8ToWide(text));
}

//--------------------------------------------------
void ofxTextLabelUL2::setText(const wstring& text)
{
    _text = text;
    _bNeedsRebuild = true;
}

//--------------------------------------------------
void ofxTextLabelUL2::appendText(const wstring& text)
{
    _text.append(text);
    _bNeedsRebuild = true;
}

//--------------------------------------------------
void ofxTextLabelUL2::appendText(const string& text){
	appendText(ofStringUTF8ToWide(text));
}

//--------------------------------------------------
void ofxTextLabelUL2::clearText()
{
    _text = L"";
    _bNeedsRebuild = true;
}

//--------------------------------------------------
void ofxTextLabelUL2::setAlign(int align)
{
    if (_align != align) {
        _align = align;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------
void ofxTextLabelUL2::setDrawShapes(bool bDrawShapes)
{
    if (_bDrawShapes != bDrawShapes) {
        _bDrawShapes = bDrawShapes;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
void ofxTextLabelUL2::setLineLength(float lineLength)
{
    if (_drawBounds.width != lineLength) {
        _drawBounds.width = lineLength;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
void ofxTextLabelUL2::setDrawBounds(const ofRectangle& drawBounds)
{
    if (_drawBounds != drawBounds) {
        if (_drawBounds.width != drawBounds.width || _drawBounds.height != drawBounds.height) {
            _bNeedsRebuild = true;
        }
        _drawBounds = drawBounds;
    }
}

//--------------------------------------------------------------
const ofRectangle& ofxTextLabelUL2::getTotalBounds()
{
    if (!_bValidTotalBounds && font.isLoaded()) {
        _totalBounds = font.getStringBoundingBox(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidTotalBounds = true;
    }
    
    return _totalBounds;
}

//--------------------------------------------------------------
const vector<ofRectangle>& ofxTextLabelUL2::getGlyphBounds()
{
    if (!_bValidGlyphBounds && font.isLoaded()) {
        _glyphBounds = font.getStringBoxes(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidGlyphBounds = true;
    }
    
    return _glyphBounds;
}
