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
  glColor3d(1.0*id/nbreId,1-1.0*id/nbreId,4.0*id/nbreId*(1-id/nbreId));
  glPushMatrix();
  glTranslatef(position[0],position[1],position[2]);
	//glutSo1idCube(1);
	
	glBegin(GL_TRIANGLES);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glNormal3f(0,0,1);
	glVertex3f(0,1,0);
	
  glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glNormal3f(0,-1,0);
	glVertex3f(0,0,1);
	
	glVertex3f(1,0,0);
	glVertex3f(0,1,0);
	glNormal3f(1,1,1);
	glVertex3f(0,0,1);
	
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glNormal3f(-1,0,0);
	glVertex3f(0,1,0);
	
	glEnd();
	
	
	glPopMatrix();
}


