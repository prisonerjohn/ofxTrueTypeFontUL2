#include "ofApp.h"
#include "ofxTextUtilsUL2.h"

int kTextMargin = 20;

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(255);
	ofNoFill();
	  
    // Setup label font first.
    
	// Load Latin face.
	textLabel.font.loadFont(OF_TTF_SERIF, 64, true, true, 0.3f, 0, true);  // OF_TTF_SERIF has arabic faces.
	
    // Load arabic face, UNICODE:0x0600-0x06FF
//    textLabel.font.loadSubFont("Traditional Arabic", 1, -0.04, 0x0600, 0x06FF) ||  // Windows
//    textLabel.font.loadSubFont("Geeza Pro", 1, -0.04, 0x0600, 0x06FF, "arab");  // OS X (Geeza need to set scriptTag)

    // Set options.
    textLabel.font.setLineHeight(textLabel.font.getFontSize() * 1.5);
//    textLabel.font.setLetterSpacing(0.1);
	textLabel.font.setTextDirection(UL2_TEXT_DIRECTION_RTL, UL2_TEXT_DIRECTION_TTB);
    textLabel.font.setStrokeWidth(1.0f);
//    textLabel.font.setAlignByPixel(true);
//    textLabel.font.setWordWrap(true);

    // Enable OT feature tags.
    // http://partners.adobe.com/public/developer/opentype/index_tag3.html
//    textLabel.font.addOTFeature("liga", 1);
    
    // This makes proportional fonts, these are OpenType features tag by "palt" or "vpal".
    // For the faces not having kerning pairs, such as Japanese fonts.
//    textLabel.font.useProportional(true);
//    textLabel.font.useVrt2Layout(true);
    
    // Build the label.
    textLabel.setAlign(UL2_TEXT_ALIGN_V_TOP | UL2_TEXT_ALIGN_RIGHT);
    textLabel.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
    
    // Load some text from a file.
    ofFile file("arabic-text.txt");
    ofBuffer buffer(file);
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        textLabel.appendText(ofStringUTF8ToWide(*it));
        textLabel.appendText(L"\n");
    }

    // Add some text programmatically.
    textLabel.appendText(L"مرحباّ بك في المستقبل\n");
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    textLabel.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(128);
    ofDrawRectangle(textLabel.getDrawBounds());
    
    if (textLabel.getDrawShapes()) {
        ofSetColor(255, 0, 0);
        textLabel.draw(0, 0);

        ofSetColor(0, 255, 0);
        ofDrawRectangle(textLabel.getTotalBounds());
        
        ofSetColor(0, 0, 255);
        for (int i = 0; i < textLabel.getGlyphBounds().size(); i++) {
            ofDrawRectangle(textLabel.getGlyphBounds()[i]);
        }
    }
    else {
        ofSetColor(0);
        textLabel.draw(0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key){
        case ' ':
            textLabel.setDrawShapes(!textLabel.getDrawShapes());
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
    textLabel.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, x - kTextMargin, y - kTextMargin));
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
    textLabel.setDrawBounds(ofRectangle(kTextMargin, kTextMargin, ofGetWidth() - kTextMargin * 2, ofGetHeight() - kTextMargin * 2));
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
