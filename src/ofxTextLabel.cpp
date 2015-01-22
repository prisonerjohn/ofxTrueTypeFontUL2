//
//  ofxTextLabel.cpp
//
//
//  Created by Elias Zananiri on 2015-01-05.
//
//

#include "ofxTextLabel.h"
#include "ofxTextUtilsUL2.h"

//--------------------------------------------------
template<typename T>
ofxTextLabel_<T>::ofxTextLabel_()
: _font(NULL)
, _text(L"")
, _drawBounds(0, 0, 0, 0)
, _bDrawShapes(false)
, _align(0)  // UL2_TEXT_ALIGN_INVALID
, _bNeedsRebuild(false)
, _bValidTotalBounds(false)
, _bValidGlyphBounds(false)
{
    
}

//--------------------------------------------------
template<typename T>
ofxTextLabel_<T>::~ofxTextLabel_()
{
    
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::rebuild()
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
template<typename T>
bool ofxTextLabel_<T>::update()
{
    if (_bNeedsRebuild && _font) {
        rebuild();
        return true;
    }
    return false;
}

//--------------------------------------------------
template<typename T>
#if OF_VERSION_MINOR > 8
void ofxTextLabel_<T>::draw(float x, float y) const
#else
void ofxTextLabel_<T>::draw(float x, float y)
#endif
{
    _fbo.draw(x, y);
}

//--------------------------------------------------
template<typename T>
#if OF_VERSION_MINOR > 8
void ofxTextLabel_<T>::draw(float x, float y, float w, float h) const
#else
void ofxTextLabel_<T>::draw(float x, float y, float w, float h)
#endif
{
    _fbo.draw(x, y, w, h);
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setFont(T *font)
{
    if (_font != font) {
        _font = font;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setText(const string& text)
{
    setText(ofStringUTF8ToWide(text));
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setText(const wstring& text)
{
    _text = text;
    _bNeedsRebuild = true;
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::appendText(const string& text)
{
    appendText(ofStringUTF8ToWide(text));
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::appendText(const wstring& text)
{
    _text.append(text);
    _bNeedsRebuild = true;
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::clearText()
{
    _text = L"";
    _bNeedsRebuild = true;
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setAlign(int align)
{
    if (_align != align) {
        _align = align;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setDrawShapes(bool bDrawShapes)
{
    if (_bDrawShapes != bDrawShapes) {
        _bDrawShapes = bDrawShapes;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setLineLength(float lineLength, float paddingX, float paddingY)
{
    // Always rebuild because we can't tell if the height has changed or not.
    //    if (_drawBounds.width != lineLength || _drawBounds.x != paddingX || _drawBounds.y != paddingY) {
    _drawBounds.set(paddingX, paddingY, lineLength, 0);
    _bNeedsRebuild = true;
    //    }
}

//--------------------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setDrawBounds(const ofRectangle& drawBounds)
{
    if (_drawBounds != drawBounds) {
        _drawBounds = drawBounds;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
template<typename T>
void ofxTextLabel_<T>::setClearColor(const ofColor &clearColor)
{
    if (_clearColor != clearColor) {
        _clearColor = clearColor;
        _bNeedsRebuild = true;
    }
}

//--------------------------------------------------------------
template<typename T>
const ofRectangle& ofxTextLabel_<T>::getTotalBounds()
{
    if (!_bValidTotalBounds && _font) {
        _totalBounds = _font->getStringBoundingBox(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidTotalBounds = true;
    }
    
    return _totalBounds;
}

//--------------------------------------------------------------
template<typename T>
const vector<ofRectangle>& ofxTextLabel_<T>::getGlyphBounds()
{
    if (!_bValidGlyphBounds && _font) {
        _glyphBounds = _font->getStringBoxes(_text, _drawBounds.x, _drawBounds.y, _drawBounds.width, _drawBounds.height, _align);
        _bValidGlyphBounds = true;
    }
    
    return _glyphBounds;
}
