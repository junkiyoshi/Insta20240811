#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 3; i++) {

		auto deg = (ofGetFrameNum() * 2 + 120 * i) % 360;
		auto location = glm::vec2(200 * cos(deg * DEG_TO_RAD), 200 * sin(deg * DEG_TO_RAD));

		color.setHsb(ofRandom(i * 64, i * 64 + 64), 255, 255);

		vector<glm::vec2> log;
		log.push_back(location);
		this->log_list.push_back(log);
		this->color_list.push_back(color);
		this->life_list.push_back(ofRandom(100, 200));
	}

	int radius = 4;
	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		this->life_list[i] -= 0.5;
		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);

			continue;
		}

		int count = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.008, count * 0.01 + ofGetFrameNum() * 0.01)), 0, 1, -360, 360);
			auto tmp = this->log_list[i].back() + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			if (glm::length(tmp) > 150 && glm::length(tmp) < 250) {

				this->log_list[i].push_back(this->log_list[i].back() + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				break;
			}
			else {

				count++;
			}
		}
		while (this->log_list[i].size() > 300) {

			this->log_list[i].erase(this->log_list[i].begin());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofRotateZ(90);

	for (int i = 0; i < this->log_list.size(); i++) {

		if (this->life_list[i] > 30) {

			ofSetColor(this->color_list[i]);
			ofSetLineWidth(1.5);
		}
		else {

			ofSetColor(ofColor(this->color_list[i], ofMap(this->life_list[i], 0, 30, 0, 255)));
			ofSetLineWidth(ofMap(this->life_list[i], 0, 30, 0, 1.5));
		}

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}