#include <iostream>
//#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Eigen/Dense>  // inclue toute la librairie Eigen
#include <math.h>
#include <time.h>
#include <vector>
#include "camera_trackball.h"
#include "Boid.h"
#include "Flock.h"
#include "Xwing.h"

using namespace std;


const float FOVY = 60.0f;
const float NEARCLIP = 0.1f;
const float FARCLIP = 100.0f;
const int FPS = 30;
const int WINDOW_X = 700;
const int WINDOW_Y = 100;
// Inputs
int mouse_x = 0;
int mouse_y = 0;
int mouse_buttons[GLUT_NUM_MOUSE_BUTTONS];
int window_w = 800;
int window_h = 600;
// Camera
CameraTrackball camera;

// Time management
float t = 0;
float last_t = 0;
float dt = 0;

static Flock<Xwing> reb;
static Flock<Tie> emp;

void init(void) 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
  
	// Init inputs
	for (int i(0); i<GLUT_NUM_MOUSE_BUTTONS; ++i) {mouse_buttons[i] = GLUT_UP;}
  
	// Init camera
	camera.init({0.0f,0.0f,0.0f}, 10.0f);
	
	// Boid initialisation
	reb = Flock<Xwing>(30,4);
	emp = Flock<Tie>(0,5);
	
}


void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Camera setup
	camera.lookAt();
    
    //Display functions
	reb.draw();
	emp.draw();

	//draw ground
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-5,-5,-5);
	glVertex3f(5,-5,-5);
	glVertex3f(5,5,-5);
	glVertex3f(-5,5,-5);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}


void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (GLfloat)w / (GLfloat)h, NEARCLIP, FARCLIP);
}


void processKeys(unsigned char key, int x, int y) 
{
	
}


void systemEvolution()
{
	last_t = t;
	t = (float)glutGet(GLUT_ELAPSED_TIME);
	dt = (t - last_t)*0.001;

	reb.move(dt,emp);
	emp.move(dt,reb);
}


void mouseButton(int button, int state, int x, int y) {
  mouse_buttons[button] = state;
  
  // Update camera
  camera.zoom(mouse_buttons[3] - mouse_buttons[4]);
}

void mousePassiveMotion(int x, int y) {
  mouse_x = x; mouse_y = y;
}

void mouseMotion(int x, int y) {
  int mouse_dx = mouse_x - x; int mouse_dy = mouse_y - y;
  float dxn = static_cast<float>(mouse_dx) / static_cast<float>(window_w);
  float dyn = -static_cast<float>(mouse_dy) / static_cast<float>(window_h);
  mouse_x = x; mouse_y = y; 

  // Update camera
  if (mouse_buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)  camera.rotate(dxn, dyn);
  if (mouse_buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN) camera.pan(dxn, dyn, 0.0f);
}

void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000 / FPS, timer, 0);
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) 
{

	glutInit(&argc, argv);
	glutInitWindowSize(window_w, window_h);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glViewport(0, 0, window_w, window_h);
	glutCreateWindow("Test window");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutKeyboardFunc(processKeys);
	glutMotionFunc(mouseMotion);


	glutIdleFunc(systemEvolution);
	glutTimerFunc(1000 / FPS, timer, 0);

	glutMainLoop();

	return 0;
}
