//
//  ofxTextLabelUL2.h
//  emptyExample
//
//  Created by Elias Zananiri on 2015-01-05.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"

//--------------------------------------------------
class ofxTextLabelUL2
: public ofBaseDraws
{
public:
    ofxTextLabelUL2();
    ~ofxTextLabelUL2();
    
    virtual void rebuild();
    virtual bool update();
    
    virtual void draw(float x, float y) const;
    virtual void draw(float x, float y, float w, float h) const;
    
    virtual float getHeight() const { return _fbo.getHeight(); }
    virtual float getWidth() const { return _fbo.getWidth(); }
    
    void setFont(ofxTrueTypeFontUL2 *font);
    ofxTrueTypeFontUL2 * getFont() { return _font; }
    
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
    
    void setLineLength(float lineLength);
    float getLineLength() { return _drawBounds.width; }
    
    void setDrawBounds(const ofRectangle& drawBounds);
    const ofRectangle& getDrawBounds() {  return _drawBounds; }
    
    void setClearColor(const ofColor& clearColor);
    const ofColor& getClearColor() { return _clearColor; }
    
    void setNeedsRebuild() { _bNeedsRebuild = true; }
    bool getNeedsRebuild() const { return _bNeedsRebuild; }
    
    const ofRectangle& getTotalBounds();
    const vector<ofRectangle>& getGlyphBounds();
    
protected:
    ofxTrueTypeFontUL2 *_font;
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
