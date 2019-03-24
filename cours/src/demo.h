#ifndef DEMO_H
#define DEMO_H
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
class Demo {
public:
	
	Demo() {}
	Demo(unsigned int nb, unsigned int nbs) : nbStates(nb), nbSubStates(nbs) {}

	virtual ~Demo() {}

	virtual void init() = 0;
	virtual void display(float t) = 0;
	virtual void lighting() = 0;


};










#endif