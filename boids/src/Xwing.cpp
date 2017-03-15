#include "Xwing.h"

void Xwing::draw() {
	glPushMatrix();
	glTranslatef(p[0],p[1],p[2]);
	drawXwing();
	glPushMatrix();
	glTranslatef(0.2*v[0],0.2*v[1],0.2*v[2]);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
}