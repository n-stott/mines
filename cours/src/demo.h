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

	void next() {
		// if (state < nbStates-1) {
			state++;
			subState = 0;
		// }
		init();
	}
	void prev() {
		// if (state > 0) {
			state--;
			subState = 0;
		// }
		init();
	}

	void snext() {
		// if (subState < nbSubStates-1)
			subState++;
		init();
	}
	void sprev() {
		// if (subState > 0)
			subState--;
		init();
	}

	unsigned int state = -1;
	unsigned int subState = 0;


private:
	unsigned int nbStates = 1;
	unsigned int nbSubStates = 1;

};










#endif