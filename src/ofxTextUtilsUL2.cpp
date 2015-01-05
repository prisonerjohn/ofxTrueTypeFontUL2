//
//  ofxTextUtilsUL2.cpp
//  emptyExample
//
//  Created by Elias Zananiri on 2015-01-05.
//
//

#include "ofxTextUtilsUL2.h"
#include "utf8.h"

wstring ofStringUTF8ToWide(const string& str)
{
    return UTF8_to_WChar(str.c_str());
}
