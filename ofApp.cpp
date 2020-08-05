#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetCircleResolution(36);

	this->color = ofColor(230, 0, 82);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();

	int deg_span = 8;
	int radius_span = 3;
	int radius_max = 800;
	int range_min = 50;
	int range_max = radius_max * 1.5;

	for (int deg = 0; deg < 360; deg += deg_span) {

		int index = this->face.getNumVertices();
		int param_2 = ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 5, sin(deg * DEG_TO_RAD) * 5, ofGetFrameNum() * 0.005), 0, 1, range_min, radius_max);
		int param_1 = param_2 * 0.5;

		for (int radius = 50; radius < radius_max; radius += radius_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), 0));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), 0));
			this->face.addVertices(vertices);

			if (radius < param_1) {

				this->face.addColor(ofColor(color, 255));
				this->face.addColor(ofColor(color, 255));

			}
			else if (radius < param_2) {

				this->face.addColor(ofColor(color, ofMap(radius, param_1, param_2, 255, 0)));
				this->face.addColor(ofColor(color, ofMap(radius, param_1, param_2, 255, 0)));
			}
			else {

				this->face.addColor(ofColor(color, 0));
				this->face.addColor(ofColor(color, 0));
			}
		}

		for (int i = index + 2; i < this->face.getNumVertices() - 2; i += 2) {

			this->face.addIndex(i + 0); this->face.addIndex(i + 1); this->face.addIndex(i + 3);
			this->face.addIndex(i + 0); this->face.addIndex(i + 3); this->face.addIndex(i + 2);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.7, ofGetHeight() * 0.28);

	ofSetColor(this->color);
	ofDrawCircle(glm::vec2(), 48);

	this->face.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}