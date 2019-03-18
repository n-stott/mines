#ifndef DEMO_H
#define DEMO_H
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
class Demo {
public:
	
	Demo() {}
	Demo(unsigned int nb) : nbStates(nb) {}

	virtual ~Demo() {}

	virtual void init() = 0;
	virtual void display(float t) = 0;
	virtual void lighting() = 0;

	void next() {
		if (state < nbStates-1) state++;
		// std::cout << state << std::endl;
		init();
	}
	void prev() {
		if (state > 0) state--;
		// std::cout << state << std::endl;
		init();
	}

	unsigned int state = 0;


private:
	unsigned int nbStates = 1;

};










#endif