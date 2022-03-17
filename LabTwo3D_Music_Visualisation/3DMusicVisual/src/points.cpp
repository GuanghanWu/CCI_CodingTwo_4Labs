#include "points.h"

points::points()
{
}
points::points(ofVec3f pos)
{
	position = pos;
}

void points::rhythm(float h, int mode)
{
	thisMode = mode;
	if (!mode) position.z = h;
	else if (mode == 1) position.z = h;
	else if (mode == 2) position.z = h;
}

void points::draw()
{//to make it possible at different drawing mode,
	if (!thisMode)
	{
		ofSetColor(position.z, 60, 200 - position.x / 8, 255 - position.x / 4);
		float r = 8.0 * (position.y / ofGetHeight());
		ofDrawBox(position.x, position.y, 0, r, r, position.z);
	}
	else if (thisMode == 1)
	{
		ofSetColor(position.z, 140, 200 - position.x / 6, 255 - position.x / 4);
		float r = 4.0 * (position.y / ofGetHeight());
		//ofDrawSphere(position, r);
		ofDrawSphere(position.x + sin(position.z) * 2.0, position.y + cos(position.z) * 2.0, position.z * 0.5f * position.y * 0.001, r);
	}
	else
	{

		ofSetColor(position.z, 220, 200 - position.x / 6, 255 - position.x / 4);
		float r = 8.0 * (position.y / ofGetHeight());
		//ofDrawSphere(position, r);
		ofRotateYDeg(90);
		ofDrawCylinder(position.x, position.y, 0, r, position.z);

	}

	//ofDrawLine(ofGetWidth() / 2, ofGetHeight(), 200, position.x, position.y, position.z);
	//ofDrawCone(position.x, position.y,(position.x+ position.y)/2000.0*(-40),6, position.z);
}
