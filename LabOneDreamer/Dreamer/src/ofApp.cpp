#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		delete path[i];
	}
	for (unsigned int i = 0; i < path2.size(); ++i)
	{
		delete path2[i];
	}
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(5, 5, 5);
	for (unsigned int i = 0; i < 20; ++i)
	{
		path.push_back(new pathObj());
	}
	for (unsigned int i = 0; i < 14; ++i)
	{
		path2.push_back(new pathObj());
	}
	for (unsigned int i = 0; i < 120; ++i)
	{
		particles.push_back(new randomObj());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	t += 0.008 + 0.006 * mouseWeight;
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		path[i]->update(t + i);
		path[i]->setMainPointPos(path[0]->getPos());
	}
	for (unsigned int i = 0; i < path2.size(); ++i)
	{
		path2[i]->update2(t + i*0.2);
		path2[i]->setMainPointPos(path2[0]->getPos());
	}

	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		/*particles[i]->update(path[i% path.size()],t);*/
		particles[i]->update(path[0], t);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		path[i]->draw(t);
	}
	for (unsigned int i = 0; i < path2.size(); ++i)
	{
		path2[i]->draw2(t);
		//cout << path2[i]->getPos().x << "  " << path2[i]->getPos().y << endl;
	}
	
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		particles[i]->draw(t);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	mouseWeight = 1.0*ofGetMouseX()/ofGetWidth()+1.0*ofGetMouseY()/ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
