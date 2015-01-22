#pragma once

#include "ofMain.h"

#define DO_FTGL
#define DO_UL2

#ifdef DO_FTGL
#include "ofxTextLabelFTGL.h"
#endif

#ifdef DO_UL2
#include "ofxTextLabelUL2.h"
#endif

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
#ifdef DO_FTGL
    void setupFTGL();
    
    ofxFTGLFontUL2 fontFTGL;
    ofxTextLabelFTGL labelFTGL;
#endif
    
#ifdef DO_UL2
    void setupUL2();

    ofxTrueTypeFontUL2 fontUL2;
    ofxTextLabelUL2 labelUL2;
#endif
};
