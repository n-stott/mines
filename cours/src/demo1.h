#ifndef DEMO1_H
#define DEMO1_H

#include "demo.h"

// Wireframe sphere
class Demo1 : public Demo {
	
public:
	Demo1() : Demo(4) {}

	void display() override {
		float r = 5;
				glColor3f(1,0,0);
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
		}
	}


};


#endif