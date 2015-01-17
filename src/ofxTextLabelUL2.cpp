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
: _font(NULL)
, _text(L"")
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
    // Calculate the height at the given width if necessary.
    if (_drawBounds.height == 0) {
        ofRectangle boundingBox = _font->getStringBoundingBox(_text, 0, 0, _drawBounds.width);
        _drawBounds.height = boundingBox.height;
    }

    // Reallocate the FBO if necessary.
    float totalWidth = _drawBounds.x * 2 + _drawBounds.width;
    float totalHeight = _drawBounds.y * 2 + _drawBounds.height;
    if (_fbo.getWidth() != totalWidth || _fbo.getHeight() != totalHeight) {
        _fboSettings.width = totalWidth;
        _fboSettings.height = totalHeight;
		_fboSettings.internalformat = GL_RGBA;
        _fbo.allocate(_fboSettings);
    }
    
    _fbo.begin();
    {
        ofClear(_clearColor.r, _clearColor.g, _clearColor.b, 0);
        
        ofPushStyle();
        
        ofSetColor(255);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
        if (_bDrawShapes) {
            _font->drawStringAsShapes(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        }
        else {
            _font->drawString(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
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
    if (_bNeedsRebuild && _font) {
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

//--------------------------------------------------
void ofxTextLabelUL2::setFont(ofxTrueTypeFontUL2 *font)
{
    if (_font != font) {
        _font = font;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------
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
void ofxTextLabelUL2::appendText(const string& text)
{
    appendText(ofStringUTF8ToWide(text));
}

//--------------------------------------------------
void ofxTextLabelUL2::appendText(const wstring& text)
{
    _text.append(text);
    _bNeedsRebuild = true;
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
void ofxTextLabelUL2::setLineLength(float lineLength, float paddingX, float paddingY)
{
    //if (_drawBounds.width != lineLength || _drawBounds.x != paddingX || _drawBounds.y != paddingY) {
        _drawBounds.set(paddingX, paddingY, lineLength, 0);
        _bNeedsRebuild = true;
    //}
}

//--------------------------------------------------------------
void ofxTextLabelUL2::setDrawBounds(const ofRectangle& drawBounds)
{
    if (_drawBounds != drawBounds) {
        _drawBounds = drawBounds;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
void ofxTextLabelUL2::setClearColor(const ofColor &clearColor)
{
    if (_clearColor != clearColor) {
        _clearColor = clearColor;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
const ofRectangle& ofxTextLabelUL2::getTotalBounds()
{
    if (!_bValidTotalBounds && _font) {
        _totalBounds = _font->getStringBoundingBox(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidTotalBounds = true;
    }
    
    return _totalBounds;
}

//--------------------------------------------------------------
const vector<ofRectangle>& ofxTextLabelUL2::getGlyphBounds()
{
    if (!_bValidGlyphBounds && _font) {
        _glyphBounds = _font->getStringBoxes(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidGlyphBounds = true;
    }
    
    return _glyphBounds;
}
