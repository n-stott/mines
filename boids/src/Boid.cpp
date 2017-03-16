#include <iostream>
#include <GL/glut.h>
#include "Boid.h"

//BOID
Boid::Boid() {
}

Boid::~Boid() {
}

void Boid::draw()
{
	float x = 0, y=0, z=0;
	glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidCube(1);
	glPopMatrix();
}
