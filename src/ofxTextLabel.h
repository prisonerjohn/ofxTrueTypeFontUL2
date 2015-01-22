//
//  ofxTextLabelUL2.h
//  emptyExample
//
//  Created by Elias Zananiri on 2015-01-05.
//
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------
template<typename T>
class ofxTextLabel_
: public ofBaseDraws
{
public:
    ofxTextLabel_();
    ~ofxTextLabel_();
    
    virtual void rebuild();
    virtual bool update();
    
#if OF_VERSION_MINOR > 8
    virtual void draw(float x, float y) const;
    virtual void draw(float x, float y, float w, float h) const;
    virtual float getHeight() const { return _fbo.getHeight(); }
    virtual float getWidth() const { return _fbo.getWidth(); }
#else
    virtual void draw(float x, float y);
    virtual void draw(float x, float y, float w, float h);
    virtual float getHeight() { return _fbo.getHeight(); }
    virtual float getWidth() { return _fbo.getWidth(); }
#endif
    
    void setFont(T *font);
    T * getFont() { return _font; }
    
    void setText(const string& text);
    void setText(const wstring& text);
    void appendText(const string& text);
    void appendText(const wstring& text);
    void clearText();
    const wstring& getText() const { return _text; }
    
    void setAlign(int align);
    int getAlign() const { return _align; }
    
    void setDrawShapes(bool bDrawShapes);
    bool getDrawShapes() const { return _bDrawShapes; }
    
    void setLineLength(float lineLength, float paddingX = 0, float paddingY = 0);
    float getLineLength() { return _drawBounds.width; }
    
    void setDrawBounds(const ofRectangle& drawBounds);
    const ofRectangle& getDrawBounds() {  return _drawBounds; }
    
    void setClearColor(const ofColor& clearColor);
    const ofColor& getClearColor() { return _clearColor; }
    
    void setNeedsRebuild() { _bNeedsRebuild = true; }
    bool getNeedsRebuild() const { return _bNeedsRebuild; }
    
	ofFbo& getFbo(){ return _fbo; }
    
    const ofRectangle& getTotalBounds();
    const vector<ofRectangle>& getGlyphBounds();
    
protected:
    T *_font;
    wstring _text;
    int _align;
    bool _bDrawShapes;
    ofRectangle _drawBounds;
    ofColor _clearColor;
    
    ofFbo _fbo;
    ofFbo::Settings _fboSettings;
    bool _bNeedsRebuild;
    
    ofRectangle _totalBounds;
    bool _bValidTotalBounds;
    
    vector<ofRectangle> _glyphBounds;
    bool _bValidGlyphBounds;
};

//--------------------------------------------------------------
typedef ofxTextLabel_<ofTrueTypeFont> ofxTextLabel;

// Include the cpp so that we can use the template with non-core font types.
// Make sure not to include the cpp in the target sources!
#include "ofxTextLabel.cpp"
