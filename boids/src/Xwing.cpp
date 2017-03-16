#include "Xwing.h"

int Xwing::style = 0;


void Xwing::incr_style() {
	Xwing::style = (++Xwing::style) % 2;
}

void Xwing::draw() {
	glPushMatrix();
	glTranslatef(p[0],p[1],p[2]);


	Eigen::Vector3f rv = v.cross(Eigen::Vector3f::UnitX());
	float cosrv = v.dot(Eigen::Vector3f::UnitX()) / v.norm();
	glRotatef( -acos(cosrv) * 180 / 3.14 , rv[0], rv[1], rv[2]);

	// Eigen::Vector3f ra = a.cross(Eigen::Vector3f::UnitZ());
	// float cosra = a.dot(Eigen::Vector3f::UnitZ()) / v.norm();
	// glRotatef( -acos(cosra) * 180 / 3.14 , rv[0], rv[1], rv[2]);


	if (Xwing::style == 0) {
		glColor3f(0,1,0);
		glutWireSphere(0.2,10,10);
	}
	else{
		drawXwing();
	}
	glPopMatrix();
	
}