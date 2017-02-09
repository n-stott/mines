#include <iostream>
//#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Eigen/Dense>  // inclue toute la librairie Eigen
#include <math.h>
#include <time.h>
#include <vector>
#include "Boid.h"

using namespace std;

int FPS = 30;
int WINDOW_X = 600;
int WINDOW_Y = 600;
int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

float t = 0;
float last_t = 0;
float dt = 0;

static Boid b;

void init(void) 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	b = Boid();
}


void display() 
{
        //Camera setup
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -1, 1,0, 0, 0, 0.0, 0.0, 1.0);

    //Display functions
	b.draw();

	glutSwapBuffers();
}


void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void processKeys(unsigned char key, int x, int y) 
{
	
}


void systemEvolution()
{
	last_t = t;
	t = (float)glutGet(GLUT_ELAPSED_TIME);
	dt = (t - last_t)*0.001;
}


void timer(int v) 
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) 
{
	
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Test window");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc();
	glutKeyboardFunc(processKeys);
	//glutMotionFunc();


	glutIdleFunc(systemEvolution);
	glutTimerFunc(1000 / FPS, timer, 0);

	glutMainLoop();
	
	return 0;
}
