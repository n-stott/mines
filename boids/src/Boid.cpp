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
	float x = 0, y=0, z=0;
	glPushMatrix();
	glTranslatef(x,y,z);
	glutSo1idCube(1);
	glPopMatrix();
}
