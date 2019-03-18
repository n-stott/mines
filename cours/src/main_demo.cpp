#include "main_demo.h"
#include "demo1.h"
// Camera
CameraTrackball camera;

std::vector<Demo*> demos;
unsigned int currentDemo = 0;
int windowId = 0;


void init() {
  
	// Init inputs
	for (int i = 0; i<GLUT_NUM_MOUSE_BUTTONS; ++i) {mouse_buttons[i] = GLUT_UP;}
  
	// Init camera
	camera.init({0.0f,0.0f,0.0f}, 10.0f);

	for(int i = 0; i < 1; ++i) {
		demos.push_back(new Demo1());
	}
	
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	//Camera setup
	camera.lookAt();
    //Display functions
    demos[currentDemo]->display(t);

	glutSwapBuffers();
}


void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (GLfloat)w / (GLfloat)h, NEARCLIP, FARCLIP);
}


void processKeys(unsigned char key, int x, int y) {
	std::cout << key << std::endl;
	if (key == 'q') exit(0);
	switch (key) {
		case 'q': {
			glutDestroyWindow(windowId);
			exit(0);
		}
	}
}

void specialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: {
			demos[currentDemo]->prev();
			break;
		}
		case GLUT_KEY_RIGHT: {
			demos[currentDemo]->next();
			break;
		}
	}
}


void systemEvolution() {
	last_t = t;
	t = (float)glutGet(GLUT_ELAPSED_TIME);
	dt = (t - last_t)*0.001;

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
	windowId = glutCreateWindow("Test window");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutKeyboardFunc(processKeys);
	glutMotionFunc(mouseMotion);
	glutSpecialFunc(specialKey);


	glutIdleFunc(systemEvolution);
	glutTimerFunc(1000 / FPS, timer, 0);

	glutMainLoop();
	
	return 0;
}
