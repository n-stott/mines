#ifndef DEMO1_H
#define DEMO1_H

#include "demo.h"

// Wireframe sphere
class Demo1 : public Demo {
	
public:
	Demo1() : Demo(10) {}

	void init() override {
		switch(state) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				break;
			case 5:


		}
		// glEnable(GL_DEPTH_TEST);
		// glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT0);
		// glEnable(GL_COLOR_MATERIAL);
		// glEnable(GL_NORMALIZE);
		// glShadeModel(GL_SMOOTH);
	}

	void display() override {
		float r = 5;
				glColor3f(1,1,1);
		switch(state) {
			case 0:
				glutWireSphere(r,4,4);
				break;
			case 1:
				glutWireSphere(r,8,8);
				break;
			case 2:
				glutWireSphere(r,20,20);
				break;
			case 3:
				glutWireSphere(r,50,50);
				break;
			case 4:
				glutWireSphere(r,20,20);
				break;
			case 5:
			case 6:
				glutSolidSphere(r,20,20);
				break;
		}
	}


};


#endif