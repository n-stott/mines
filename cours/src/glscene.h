#ifndef GLSCENE_H
#define GLSCENE_H

#include <iostream>
//#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include "camera_trackball.h"
#include "glObject.h"
#include <vector>
#include "Time.h"


class glScene {
public:
	// Scary _s to make things seem important
	static void _createWindow_(int argc, char** argv);

	static void _setCallbacks_();

	static void _start_();

	static void addObject(glObject* obj);

private:
	// Pointers to objects in the scene
	static std::vector<glObject*> objects;

	// Camera
	static CameraTrackball camera;

	// OpenGL window parameters
	static const float FOVY; // = 60.0f;
	static const float NEARCLIP; // = 0.1f;
	static const float FARCLIP; // = 10000.0f;
	static const int FPS; // = 30;
	static const int WINDOW_X; // = 700;
	static const int WINDOW_Y; // = 100;

	// Inputs
	static int mouse_x; // = 0;
	static int mouse_y; // = 0;
	static int mouse_buttons[];
	static int window_w; // = 800;
	static int window_h; // = 600;

	// Time management
	static Time time;

	// Reference to current window
	static int windowId;

	// openGl initialization
	static void init();

	// Callbacks
	static void display();
	static void systemEvolution();
	static void reshape(int w, int h);
	static void mouseButton(int button, int state, int x, int y);
	static void mouseMotion(int x, int y);
	static void mousePassiveMotion(int x, int y);
	static void processKeys(unsigned char key, int x, int y);
	static void specialKey(int key, int x, int y);
	static void timer(int v);

	// Utility 
	static void updateTime();
};

std::vector<glObject*> glScene::objects(0);

CameraTrackball glScene::camera;

const float glScene::FOVY = 60.0f;
const float glScene::NEARCLIP = 0.1f;
const float glScene::FARCLIP = 10000.0f;
const int glScene::FPS = 30;
const int glScene::WINDOW_X = 700;
const int glScene::WINDOW_Y = 100;

// Inputs
int glScene::mouse_x = 0;
int glScene::mouse_y = 0;
int glScene::mouse_buttons[GLUT_NUM_MOUSE_BUTTONS];
int glScene::window_w = 800;
int glScene::window_h = 600;

int glScene::windowId = 0;

Time glScene::time;

// Scary _s to make things seem important
void glScene::_createWindow_(int argc, char** argv) {
	// Init inputs
	for (int i = 0; i<GLUT_NUM_MOUSE_BUTTONS; ++i)
		mouse_buttons[i] = GLUT_UP;
	// Init camera
	camera.init({0.0f,0.0f,0.0f}, 10.0f);
	// Init glut and create window
	glutInit(&argc, argv);
	glutInitWindowSize(window_w, window_h);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glViewport(0, 0, window_w, window_h);
	windowId = glutCreateWindow("Test window");
}

void glScene::_setCallbacks_() {
	glutDisplayFunc(display);
	glutIdleFunc(systemEvolution);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutKeyboardFunc(processKeys);
    glutMotionFunc(mouseMotion);
    glutSpecialFunc(specialKey);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void glScene::_start_() {
	init();
	glutMainLoop();
}

void glScene::init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);		
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void glScene::addObject(glObject* obj) {
	objects.push_back(obj);
}

void glScene::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Camera setup
	camera.lookAt();
	//Display objects
	for(glObject* obj : objects)
		obj->display(time);
	glutSwapBuffers();
}

void glScene::systemEvolution() {
	updateTime();
	for(glObject* obj : objects)
		obj->move(time);
}

void glScene::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (GLfloat)w / (GLfloat)h, NEARCLIP, FARCLIP);
}


void glScene::mouseButton(int button, int state, int x, int y) {
	mouse_buttons[button] = state;
	// Update camera
	camera.zoom(mouse_buttons[3] - mouse_buttons[4]);
}

void glScene::mousePassiveMotion(int x, int y) {
	mouse_x = x; mouse_y = y;
}

void glScene::mouseMotion(int x, int y) {
	int mouse_dx = mouse_x - x; int mouse_dy = mouse_y - y;
	float dxn = static_cast<float>(mouse_dx) / static_cast<float>(window_w);
	float dyn = -static_cast<float>(mouse_dy) / static_cast<float>(window_h);
	mouse_x = x; mouse_y = y; 

	// Update camera
	if (mouse_buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)  camera.rotate(dxn, dyn);
	if (mouse_buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN) camera.pan(dxn, dyn, 0.0f);
}

void glScene::timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}


void glScene::processKeys(unsigned char key, int x, int y) {
	switch (key) {
		case 'q': {
			glutDestroyWindow(windowId);
			exit(0);
		}
	}
}

void glScene::specialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: {
			// glObject::prev();
			break;
		}
		case GLUT_KEY_RIGHT: {
			// glObject::next();
			break;
		}
		case GLUT_KEY_UP: {
			// glObject::snext();
			break;
		}
		case GLUT_KEY_DOWN: {
			// glObject::sprev();
			break;
		}
	}
}


void glScene::updateTime() {
	time.update((float)glutGet(GLUT_ELAPSED_TIME));
}


#endif