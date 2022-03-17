#include "objects.h"



void object::setPos(ofVec3f p)
{
	this->pos = p;
}

void object::setVel(ofVec3f v)
{
	this->vel = v;
}

void object::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void object::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f object::getPos()
{
	return this->pos;
}

ofVec3f object::getVel()
{
	return this->vel;
}

float object::getAppealHood()
{
	return this->appealHood;
}

float object::getRepelHood()
{
	return this->repelHood;
}

ofVec3f object::appeal()
{
	return ofVec3f();
}

ofVec3f object::repel()
{
	return ofVec3f();
}

void object::update()
{
}

void object::draw()
{
}



/* pathObj's definitions : */

pathObj::pathObj()
{
	/*this->pos = ofVec3f(ofRandom(100), ofRandom(100));
	this->vel = ofVec3f(ofRandom(5), ofRandom(5));*/
	setPos(ofVec3f(ofRandom(100), ofRandom(100)));
	setVel(ofVec3f(ofRandom(5), ofRandom(5)));
}

pathObj::pathObj(ofVec3f posIn, ofVec3f velIn)
{
	this->pos = posIn;
	this->vel = velIn;
}

//pathObj::~pathObj()
//{
//}
void pathObj::setPos(ofVec3f p)
{
	this->pos = p;
}

void pathObj::setMainPointPos(ofVec3f p)
{
	mainPointPos = p;
}

void pathObj::setVel(ofVec3f v)
{
	this->vel = v;
}

void pathObj::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void pathObj::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f pathObj::getPos()
{
	return this->pos;
}

ofVec3f pathObj::getMainPointPos()
{
	return mainPointPos;
}

ofVec3f pathObj::getVel()
{
	return this->vel;
}

float pathObj::getAppealHood()
{
	return this->appealHood;
}

float pathObj::getRepelHood()
{
	return this->repelHood;
}


void pathObj::update(float t)
{
	float r = sin(t) * sqrt(abs(cos(t))) / (sin(t) + 1.4) - 2 * sin(t) + 2;
	ofVec2f pos2D = ofVec2f(r * cos(t) * 200 + ofGetWidth() / 2, -1 * (r * sin(t) * 200) + ofGetHeight() / 4);
	this->setPos(ofVec3f(pos2D));
	
}
void pathObj::update2(float t)
{
	float r = 2 * abs(sin(2.0 * t)) + abs(sin(4.0 * t));
	ofVec2f pos2D = ofVec2f(r * cos(t) * 80 + ofGetWidth() / 2,  (r * sin(t) *80) + ofGetHeight()/2- ofGetHeight()/22);
	this->setPos(ofVec3f(pos2D));

}

void pathObj::draw(float t)
{	float dis = pos.distance(mainPointPos);
	ofSetColor(200- dis/2, 80- dis/6, int(t*10)%255);
	ofDrawCircle(pos, 8);
}

void pathObj::draw2(float t)
{
	float dis = pos.distance(mainPointPos);
	ofSetColor(100 - dis / 2, 180 - dis / 2, 50 + int(t * 10) % 200);
	ofDrawCircle(pos, 4);
}

//Now come the randomPathObjects!

randomObj::randomObj()
{
	this->pos = ofVec3f(ofRandom(500), ofRandom(500));
	this->vel = ofVec3f(ofRandom(1), ofRandom(1));

	this->appealWeight = 1.4;
	this->repelWeight = 0.4;
	this->appealHood = 1800;
	this->repelHood = 60;
}

randomObj::randomObj(ofVec3f posIn, ofVec3f velIn, float aW, float rW, float aH, float rH)
{
	this->pos = posIn;
	this->vel = velIn;
	this->appealWeight = aW;
	this->repelWeight = rW;
	this->appealHood = aH;
	this->repelHood = rH;
}

//randomObj::~randomObj()
//{
//}

void randomObj::setPos(ofVec3f p)
{
	this->pos = p;
}

void randomObj::setVel(ofVec3f v)
{
	this->vel = v;
}

void randomObj::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void randomObj::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f randomObj::getPos()
{
	return this->pos;
}

ofVec3f randomObj::getVel()
{
	return this->vel;
}

float randomObj::getAppealHood()
{
	return this->appealHood;
}

float randomObj::getRepelHood()
{
	return this->repelHood;
}


ofVec3f randomObj::appeal(pathObj* otherObj)
{
	ofVec3f v(0, 0, 0);
	if (pos.distance(otherObj->getPos()) < appealHood)
	{
		v = otherObj->getPos() - pos;
	}
	
	v.normalize();
	return v;
};


ofVec3f randomObj::appeal(vector < pathObj*>& otherObj)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (unsigned int i = 0; i < otherObj.size(); i++)
	{
		if (pos.distance(otherObj[i]->getPos()) < appealHood)
		{
			average += otherObj[i]->getPos();
			count += 1;//count =  count + 1;
		}
	}
	average /= count;
	ofVec3f v = average - pos;
	v.normalize();
	return v;
};

ofVec3f randomObj::repel(pathObj* otherObj)
{
	ofVec3f v(0, 0, 0);
	if (pos.distance(otherObj->getPos()) < repelHood)
	{
		v = pos - otherObj->getPos();
	}
	v.normalize();
	return v;
};


ofVec3f randomObj::repel(vector < pathObj*> & otherObj)
{
	return ofVec3f();
};

void randomObj::update(pathObj* otherObj, float t)
{
	vel += repel(otherObj) * repelWeight;
	vel += appeal(otherObj) * appealWeight;
	pos += vel;

	float para = 0.4;
	vel.x = pos.x > ofGetWidth() ? -vel.x * para : vel.x;//Three-Issue-Structure to take place of the Walls-Function
	vel.x = pos.x < FLT_MIN ? -vel.x * para : vel.x;
	vel.y = pos.y > ofGetHeight() ? -vel.y * para : vel.y;
	vel.y = pos.y < FLT_MIN ? -vel.y * para : vel.y;

	distance = pos.distance(otherObj->getPos());
};

void randomObj::update(vector < pathObj*> & otherObj, float t)
{
	vel += repel(otherObj)*repelWeight;
	vel += appeal(otherObj)*appealWeight;
	pos += vel;
};

void randomObj::draw(float t)
{
	ofSetColor(int(t * 5) % 255, 180- distance/3,200- distance/3);
	ofDrawCircle(pos, 2.4);
}
