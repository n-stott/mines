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
	glutSo1idCube(1);
}
