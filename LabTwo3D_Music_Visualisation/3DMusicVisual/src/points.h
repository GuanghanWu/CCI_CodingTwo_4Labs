#pragma once
#include "ofMain.h"
class points
{
public:
	points();
	points(ofVec3f pos);
	ofVec3f position;
	int thisMode=0;
	void rhythm(float h, int mode=0);
	void draw();
};