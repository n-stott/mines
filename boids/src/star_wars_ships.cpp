#include "star_wars_ships.h"

void drawXwing() {
	glColor3f(1,1,1);
	float r = 0.4;
	glScalef(r,r,r);
	glPushMatrix();
		glRotatef(90,0,1,0);
		glutSolidCone(0.15,0.8,4,10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.2,0.2,0.05);
		glRotatef(30,1,0,0);
		glScalef(1,3,0.2);
		glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.2,0.2,-0.05);
		glRotatef(-30,1,0,0);
		glScalef(1,3,0.2);
		glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.2,-0.2,-0.05);
		glRotatef(30,1,0,0);
		glScalef(1,3,0.2);
		glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.2,-0.2,0.05);
		glRotatef(-30,1,0,0);
		glScalef(1,3,0.2);
		glutSolidCube(0.2);
	glPopMatrix();
}

void drawTie() {
	glColor3f(0.1,0.1,0.1);
    GLUquadricObj *obj = gluNewQuadric();
	glutSolidSphere(0.05,20,20);
	glPushMatrix();
		glScalef(0.2,1,0.2);
		glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0.15,0);
		glRotatef(90,1,0,0);
		glScalef(0.8,1,1);
    	gluCylinder(obj, 0.2, 0.2, 0.02, 10, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.15,0);
		glRotatef(90,1,0,0);
		glScalef(0.8,1,1);
    	gluCylinder(obj, 0.2, 0.2, 0.02, 10, 5);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,0.15,0);
		glRotatef(90,1,0,0);
		glScalef(0.8,1,1);
    	gluDisk(obj, 0, 0.2, 10, 5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.15,0);
		glRotatef(90,1,0,0);
		glScalef(0.8,1,1);
    	gluDisk(obj, 0, 0.2,  10, 5);
	glPopMatrix();
}