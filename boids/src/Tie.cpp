#include "Tie.h"

int Tie::style = 0;


void Tie::incr_style() {
	Tie::style = (++Tie::style) % 2;
}

void Tie::draw() {
	glPushMatrix();
	glTranslatef(p[0],p[1],p[2]);
	
	Eigen::Vector3f rv = v.cross(Eigen::Vector3f::UnitX());
	float cosrv = v.dot(Eigen::Vector3f::UnitX()) / v.norm();
	glRotatef( -	acos(cosrv) * 180 / 3.14 , rv[0], rv[1], rv[2]);


	if (Tie::style == 0) {
		glColor3f(1,0,0);
		glutWireSphere(0.2,10,10);
	}
	else {
		drawTie();
	}
	glPopMatrix();
}