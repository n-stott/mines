#include <iostream>
#include <GL/glut.h>
#include "Boid.h"
#include "ttime.h"

//BOID
Boid::Boid() {
}

Boid::~Boid() {
}

void Boid::draw()
{
	glPointSize(20.0);
        glBegin(GL_POINTS);
        glColor3f(1.0,1.0,0.0);
	glVertex3(0.0,0.0,0.0);
        glEnd();
}
