#include "star_wars_ships.h"

void drawXwing() {
	glColor3f(1,1,1);
	glutSolidCube(0.2);
	glColor3f(1,0,0);
	glutWireSphere(0.2,10,10);
}

void drawTie() {
	glutSolidSphere(0.2,20,20);
}