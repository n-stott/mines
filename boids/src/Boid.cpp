#include "Boid.h"
#include "Xwing.h"
#include "Tie.h"
//BOID
Boid::Boid() {
	p = Eigen::Vector3f(0,0,0);
	v = Eigen::Vector3f(0,0,0);
	a = Eigen::Vector3f(0,0,0);
	prey = false;
}

Boid::Boid(Eigen::Vector3f pi, Eigen::Vector3f vi, Eigen::Vector3f ai) : p(pi), v(vi), a(vi), prey(false) {
}

Boid::Boid(float i, float e) {
	p = Eigen::Vector3f(rand(i,e),rand(i,e),0);
	v = 0.2*Eigen::Vector3f(rand(i,e),rand(i,e),0);
	a = Eigen::Vector3f(0,0,0);
	prey = false;
}


template<class T>
float Boid::d(T const &b) const {
	return (p - b.p).norm();
}

template float Boid::d<Boid>(Boid const &) const;
template float Boid::d<Tie>(Tie const &) const;
template float Boid::d<Xwing>(Xwing const &) const;


template<class T>
bool Boid::sees(T const &b) const {
	return ( v.dot( b.p - p ) > 0 );
}

template bool Boid::sees<Boid>(Boid const &) const;
template bool Boid::sees<Tie>(Tie const &) const;
template bool Boid::sees<Xwing>(Xwing const &) const;

Eigen::Vector3f Boid::steer(Eigen::Vector3f vc) const {
	float n = vc.norm();
	if (n > 0.01) {
		Eigen::Vector3f w = vc.normalized();
		w = max_speed*w - v;
		return w;
	}
	else {
		return Eigen::Vector3f::Zero();
	}

}


void Boid::move(Eigen::Vector3f ac, float dt) {
	a = limit(ac, max_force);
	v = limit(v + dt*a, max_speed);
	p = p + dt*v;
}

void Boid::contain(float b) {
	// Eigen::Vector3f w(0,0,0);
	// w[0] = sat(p[0],-b,b);
	// w[1] = sat(p[1],-b,b);
	// w[2] = sat(p[2],-b,b);
	// v[0] = (abs(w[0] - p[0]) < 0.001)*v[0];
	// v[1] = (abs(w[1] - p[1]) < 0.001)*v[1];
	// v[2] = (abs(w[2] - p[2]) < 0.001)*v[2];
	p[0] = loop(p[0],-b,b);
	p[1] = loop(p[1],-b,b);
	p[2] = loop(p[2],-b,b);
}

void Boid::draw()
{
	glPushMatrix();
	glTranslatef(p[0],p[1],p[2]);
	glScalef(0.3,0.3,0.3);
	glutSolidCube(1);
	glPopMatrix();
}
