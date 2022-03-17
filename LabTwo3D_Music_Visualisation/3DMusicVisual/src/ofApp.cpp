#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp()
{
	for (unsigned int i = 0; i < pointStore.size(); ++i)
	{
		for (unsigned int j = 0; j < pointStore[0].size(); ++j)
		{
			delete pointStore[i][j];
		}
	}
}
//--------------------------------------------------------------
void ofApp::setup(){
	myMusic.load("music/RFJN.mp3");
	myMusic.setVolume(0.8f);
	

	ofSetVerticalSync(true);

	for (unsigned int i = 0; i < 128; ++i)
	{
		temp.clear();
		for (unsigned int j = 0; j < 20; ++j)
		{
			points* p = new points(ofVec3f(100.0 + i * 10, ofGetHeight() / 10 + float(j) * ofGetHeight() / 25.0));
			temp.push_back(p);
			//initial 2D positions of points.
		}
		pointStore.push_back(temp);

	}

}

//--------------------------------------------------------------
void ofApp::update(){

	float* val = ofSoundGetSpectrum(nBand);	
	for (unsigned int i = 0; i < nBand; i++) {
		fft[i] *= 0.94f;//this right value higher, the display smoother.
		if (fft[i] < val[i]) fft[i] = val[i];
	}
	//then the fft[] from index 0 to nBand-1 has its own value from the bg music.
	//cout<<*val<<endl;

	for (unsigned int i = 0; i < pointStore.size(); ++i)
	{
		for (unsigned int j = 0; j < pointStore[0].size(); ++j)
		{
			pointStore[i][j]->rhythm(fft[i] * 800,mode);
		}
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::black, ofColor(20, 20, 20), OF_GRADIENT_CIRCULAR);
	cam.begin();
	ofEnableDepthTest();

	for (unsigned int i = 0; i < pointStore.size(); ++i)
	{
		for (unsigned int j = 0; j < pointStore[0].size(); ++j)
		{
			pointStore[i][j]->draw();
		}
	}
	

	ofDisableDepthTest();
	cam.end();
	ofSetColor(200);
	float width = (float)(8 * 128) / nBand;
	/*for (unsigned int i = 0; i < nBand; i++) {
		ofDrawRectangle(100 + i * width, ofGetHeight() - 100, width, -(fft[i] * 400));
	}*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//cout << "key" << ofToString(key)  << endl;
	if(key == 32) mode = (mode + 1) % 3;//After test, my key BACKSPACE is 32, so this is the meaning of rightValue 32.
	if(key == 103)myMusic.play(); // in my keyBoard, g is 103 ; press "g" to reset the play.
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//cout << "x: " << x << "y: " << y << "button: " << button << endl;

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
