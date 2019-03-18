#ifndef DEMO_H
#define DEMO_H
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
class Demo {
public:
	
	Demo() {}
	Demo(unsigned int nb) : nbStates(nb) {}

	virtual void display() = 0;

	void next() {
		if (state < nbStates-1) state++;
		std::cout << state << std::endl;
	}
	void prev() {
		if (state > 0) state--;
		std::cout << state << std::endl;
	}

	unsigned int state = 0;
private:
	unsigned int nbStates = 1;

};










#endif