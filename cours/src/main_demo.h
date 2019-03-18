#include <iostream>
//#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Eigen/Dense>  // inclue toute la librairie Eigen
#include <math.h>
#include <time.h>
#include <vector>
#include "camera_trackball.h"

using namespace std;


const float FOVY = 60.0f;
const float NEARCLIP = 0.1f;
const float FARCLIP = 10000.0f;
const int FPS = 30;
const int WINDOW_X = 700;
const int WINDOW_Y = 100;
// Inputs
int mouse_x = 0;
int mouse_y = 0;
int mouse_buttons[GLUT_NUM_MOUSE_BUTTONS];
int window_w = 800;
int window_h = 600;
// Time management
float t = 0;
float last_t = 0;
float dt = 0;
