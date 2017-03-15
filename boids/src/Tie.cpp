#include "Tie.h"

void Tie::draw() {
	glPushMatrix();
	glTranslatef(p[0],p[1],p[2]);
	drawTie();
	glPopMatrix();
}