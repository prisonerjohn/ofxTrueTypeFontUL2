#include "ofApp.h"
#include "ofxTextUtilsUL2.h"

int kTextMargin = 20;

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(255);
	ofNoFill();

#ifdef DO_FTGL
    setupFTGL();
#endif
    
#ifdef DO_UL2
    setupUL2();
#endif
}

#ifdef DO_FTGL
//--------------------------------------------------------------
void ofApp::setupFTGL()
{
    // Setup label font first.
    
    // Load Latin face.
    if (!fontFTGL.loadFont("mplus-1c-regular.ttf", 32)) {
        ofLogError("ofApp::setupFTGL") << "Could not load font file " << "mplus-1c-regular.ttf";
    }
	
    // Set options.
    fontFTGL.setLineSpacing(1.5);
    
    // Set the label font.
    labelFTGL.setFont(&fontFTGL);
    
    // Build the label.
    labelFTGL.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
    
    // You can also just set the length and the label will calculate its height automatically, with optional padding.
    //    labelFTGL.setLineLength(ofGetWidth() - kTextMargin * 2, kTextMargin, kTextMargin);
    
    // Add some text programmatically.
    labelFTGL.appendText("Here is some FTGL test text.");
}
#endif

#ifdef DO_UL2
//--------------------------------------------------------------
void ofApp::setupUL2()
{
    // Setup label font first.
    
    // Load Latin face.
    if (!fontUL2.loadFont(OF_TTF_SERIF, 64, true, true, 0.3f, 0, true)) {  // OF_TTF_SERIF has arabic faces.
        ofLogError("ofApp::setupUL2") << "Could not load font file " << OF_TTF_SERIF;
    }
	
    // Load arabic face, UNICODE:0x0600-0x06FF
//    fontUL2.loadSubFont("Traditional Arabic", 1, -0.04, 0x0600, 0x06FF) ||  // Windows
//    fontUL2.loadSubFont("Geeza Pro", 1, -0.04, 0x0600, 0x06FF, "arab");  // OS X (Geeza need to set scriptTag)
    
    // Set options.
    fontUL2.setLineHeight(fontUL2.getFontSize() * 1.5);
//    fontUL2.setLetterSpacing(0.1);
	fontUL2.setTextDirection(UL2_TEXT_DIRECTION_RTL, UL2_TEXT_DIRECTION_TTB);
    fontUL2.setStrokeWidth(1.0f);
//    fontUL2.setAlignByPixel(true);
//    fontUL2.setWordWrap(true);
    
    // Enable OT feature tags.
    // http://partners.adobe.com/public/developer/opentype/index_tag3.html
//    fontUL2.addOTFeature("liga", 1);
    
    // This makes proportional fonts, these are OpenType features tag by "palt" or "vpal".
    // For the faces not having kerning pairs, such as Japanese fonts.
//    fontUL2.useProportional(true);
//    fontUL2.useVrt2Layout(true);
    
    // Set the label font.
    labelUL2.setFont(&fontUL2);
    
    // Build the label.
    labelUL2.setAlign(UL2_TEXT_ALIGN_V_TOP | UL2_TEXT_ALIGN_RIGHT);
    labelUL2.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
    
    // You can also just set the length and the label will calculate its height automatically, with optional padding.
//    labelUL2.setLineLength(ofGetWidth() - kTextMargin * 2, kTextMargin, kTextMargin);
    
    // Load some text from a file.
    ofFile file("arabic-text.txt");
    ofBuffer buffer(file);
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        labelUL2.appendText(ofStringUTF8ToWide(*it));
        labelUL2.appendText(L"\n");
    }
    
    // Add some text programmatically.
    labelUL2.appendText(L"مرحباّ بك في المستقبل\n");
}
#endif

//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
#ifdef DO_FTGL
    labelFTGL.update();
    cout << "ftgl string bounds = " << fontFTGL.ofxFTGLSimpleLayout::getStringBoundingBox("Here is some FTGL test text.", 0, 0) << endl;
    cout << "label draw bounds = " << labelFTGL.getDrawBounds() << endl;
#endif
    
#ifdef DO_UL2
    labelUL2.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(128);
    ofDrawRectangle(labelUL2.getDrawBounds());
    
#ifdef DO_FTGL
    ofSetColor(0);
//    labelFTGL.draw(0, 0);
    
    fontFTGL.setLineLength(labelFTGL.getLineLength());
    fontFTGL.drawString("Here is some FTGL test text.", kTextMargin, kTextMargin);
#endif

#ifdef DO_UL2
    if (labelUL2.getDrawShapes()) {
        ofSetColor(255, 0, 0);
        labelUL2.draw(0, 0);

        ofSetColor(0, 255, 0);
        ofDrawRectangle(labelUL2.getTotalBounds());
        
        ofSetColor(0, 0, 255);
        for (int i = 0; i < labelUL2.getGlyphBounds().size(); i++) {
            ofDrawRectangle(labelUL2.getGlyphBounds()[i]);
        }
    }
    else {
        ofSetColor(0);
        labelUL2.draw(0, 0);
    }
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key) {
        case ' ':
#ifdef DO_UL2
            labelUL2.setDrawShapes(!labelUL2.getDrawShapes());
#endif
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
#ifdef DO_FTGL
    labelFTGL.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, x - kTextMargin, y - kTextMargin));
#endif
#ifdef DO_UL2
    labelUL2.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, x - kTextMargin, y - kTextMargin));
#endif
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
#ifdef DO_FTGL
    labelFTGL.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
#endif
#ifdef DO_UL2
    labelUL2.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
#endif
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
