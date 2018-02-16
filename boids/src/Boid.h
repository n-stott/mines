#ifndef BOIDS_H
#define BOIDS_H

#include <iostream>

#include <GL/glut.h>

#include <Eigen/Dense>
#include "math_u.h"

class Boid {
public:
	// Constructor
	explicit Boid();
	explicit Boid(Eigen::Vector3f pi, Eigen::Vector3f vi, Eigen::Vector3f ai);
	explicit Boid(float i, float e);
	
	Eigen::Vector3f p;
	Eigen::Vector3f v;
	Eigen::Vector3f a;

	bool prey;

	float r_sep = 2;
	float r_align = 4;
	float r_cohe = 3;

	float max_force = 3;
	float max_speed = 5;


	template<class T>
	float d(T const &b) const;

	template<class T>
	bool sees(T const &b) const;

	Eigen::Vector3f steer(Eigen::Vector3f vc) const;
	void move(Eigen::Vector3f vc, float dt);
	void contain(float b);

	virtual void draw();



	
};

#endif